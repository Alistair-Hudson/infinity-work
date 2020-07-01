#include <stdlib.h>
#include <stdio.h>

/*=====PublicTransport=====*/
static int s_count = 0;

struct PublicTransport;

struct PTVTable
{
    void (*Destructor)(struct PublicTransport*);
    void (*display)(struct PublicTransport*);
};

struct PublicTransport
{
    struct PTVTable* vtable;
    int m_license_plate;
};

void PTDestructor(struct PublicTransport* ptransport)
{
    --s_count;
    printf("PublicTransport::Dtor()\n");
}

void PTDisplay(struct PublicTransport* ptransport)
{
    printf("PublicTransport::display(): %d\n", ptransport->m_license_plate);
}

static struct PTVTable g_ptvtable = {PTDestructor, PTDisplay};

void PTConstructor(struct PublicTransport* ptransport)
{
    ++s_count;
    ptransport->m_license_plate = s_count;
    ptransport->vtable = &g_ptvtable;
    printf("PublicTransport::Ctor() %d\n", ptransport->m_license_plate);
}

void PTCopy(struct PublicTransport* ptransport, const struct PublicTransport* other)
{
    ++s_count;
    ptransport->vtable = other->vtable;
    ptransport->m_license_plate = s_count;
    printf("PublicTransport::CCtor() %d\n", ptransport->m_license_plate);
}

static void PrintCount()
{
    printf("s_count: %d\n", s_count);
}

static int GetId(const struct PublicTransport* ptransport)
{
    return ptransport->m_license_plate;
}

/*=====Minibus=====*/
struct Minibus;

struct MVTable
{
    struct PTVTable* ptable;
    void (*wash)(struct Minibus*, int);
};

struct Minibus
{
    struct PublicTransport ptransport;
    struct PTVTable* vtable;
    void (*wash)(struct Minibus*, int); 
    int m_numSeats;
};

void MDestructor(struct Minibus* minibus)
{
    printf("Minibus::Dtor()\n");
    PTDestructor(&minibus->ptransport);
}

void MDisplay(struct Minibus* minibus)
{
    printf("Minibus::display() ID: %d\n", GetId(&minibus->ptransport));
    printf("num seats: %d\n", minibus->m_numSeats);
}

void MWash(struct Minibus* minibus, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, GetId(&minibus->ptransport));
}

static struct PTVTable g_mvtable = {MDestructor, MDisplay};

void MConstructor(struct Minibus* minibus)
{
    PTConstructor(&minibus->ptransport);
    minibus->vtable = &g_mvtable;
    minibus->wash = MWash;
    minibus->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void MCopy(struct Minibus* minibus, const struct Minibus* other)
{
    PTCopy(&minibus->ptransport, &other->ptransport);
    minibus->m_numSeats  = other->m_numSeats;
    minibus->vtable = other->vtable;
    printf("Minibus::CCtor()\n");
}

/*=====Taxi=====*/

struct Taxi;

struct TVtable
{
    struct PTVTable* ptable;
};

struct Taxi
{
  struct PublicTransport ptransport;
  struct PTVTable* vtable;
};

void TDestructor(struct Taxi* taxi)
{
    printf("Taxi::Dtor()\n");
    PTDestructor(&taxi->ptransport);
}

void TDisplay(const struct Taxi* taxi)
{
    printf("Taxi::display() ID: %d\n", GetId(&taxi->ptransport));
}

static struct PTVTable g_tvtable = {TDestructor, TDisplay};

void TConstructor(struct Taxi* taxi)
{
    PTConstructor(&taxi->ptransport);
    taxi->vtable = &g_tvtable;
    printf("Taxi::Ctor()\n");
}

void TCopy(struct Taxi* taxi, const struct Taxi* other)
{
    PTCopy(&taxi->ptransport, &other->ptransport);
    taxi->vtable = other->vtable;
    printf("Taxi::CCtor()\n");
}

/*=====template======*/
int max_func(const int t1, const int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

/*====SpecialTaxi=====*/

struct SpecialTaxi
{
    struct Taxi taxi;
    struct PTVTable* vtable;
};

void STDestructor(struct SpecialTaxi* staxi)
{
    printf("SpecialTaxi::Dtor()\n");
    TDestructor(&staxi->taxi);
}

void STDisplay(const struct SpecialTaxi* staxi)
{
    printf("SpecialTaxi::display() ID: %d", GetId(&staxi->taxi.ptransport));
}

static struct PTVTable g_stvtable = {STDestructor, STDisplay};

void STConstructor(struct SpecialTaxi* staxi)
{
    TConstructor(&staxi->taxi);
    staxi->vtable = &g_stvtable;
    printf("SpecialTaxi::Ctor()\n");
}

void STCopy(struct SpecialTaxi* staxi, struct SpecialTaxi* other)
{
    TCopy(&staxi->taxi, &other->taxi);
    printf("SpecialTaxi::CCtor()\n");
}

/*==== PublicConvoy ====*/
struct PublicConvoy
{
    struct Minibus* m_pt1;
    struct Taxi* m_pt2;
    struct Minibus m_m;
    struct Taxi m_t;
};

void PCConstructor(struct PublicConvoy* pconvoy)
{
    pconvoy->m_pt1 = malloc(sizeof(struct Minibus));
    MConstructor(pconvoy->m_pt1);
    pconvoy->m_pt2 = malloc(sizeof(struct Taxi));
    TConstructor(pconvoy->m_pt2);
    
    MConstructor(&pconvoy->m_m);
    TConstructor(&pconvoy->m_t);
}

void PCCopy(struct PublicConvoy* pconvoy, const struct PublicConvoy* other)
{
    pconvoy->m_pt1 = malloc(sizeof(struct Minibus));
    MCopy(pconvoy->m_pt1, other->m_pt1);
    pconvoy->m_pt2 = malloc(sizeof(struct Taxi));
    TCopy(pconvoy->m_pt2, other->m_pt2);
    
    MCopy(&pconvoy->m_m, &other->m_m);
    TCopy(&pconvoy->m_t, &other->m_t);
}

void PCDestructor(struct PublicConvoy* pconvoy)
{
    TDestructor(&pconvoy->m_t);
    MDestructor(&pconvoy->m_m);
    TDestructor(pconvoy->m_pt2);
    MDestructor(pconvoy->m_pt1);
    free(pconvoy->m_pt1);
    free(pconvoy->m_pt2);
}

void PCDisplay(struct PublicConvoy* pconvoy)
{
    MDisplay(pconvoy->m_pt1);
    TDisplay(pconvoy->m_pt2);
    MDisplay(&pconvoy->m_m);
    TDisplay(&pconvoy->m_t);
}


/*====Other functions=====*/
void PT_print_info(struct PublicTransport* a)
{
    PTDisplay(a);
}

void print_info()
{
    PrintCount();
}

void M_print_info(struct Minibus* m)
{
    m->wash(m, 3);
}

struct PublicTransport int_print_info(int i)
{
    struct Minibus ret;
    MConstructor(&ret);
    printf("print_info(int i)\n");
    MDisplay(&ret);
    return ret.ptransport;
}

void taxi_display(struct Taxi* s)
{
    TDisplay(s);
}

union PTunion
{
    struct PublicTransport* pt;
    struct Minibus* mb;
    struct Taxi* tx;
};

int main(int argc, char **argv, char **envp)
{
    struct Minibus m;
    MConstructor(&m);
    M_print_info(&m);
    struct PublicTransport pt = int_print_info(3);
    PTDisplay(&pt);
    
    struct Minibus* a1 = malloc(sizeof(struct Minibus));
    MConstructor(a1);
    struct Taxi* a2 = malloc(sizeof(struct Taxi));
    TConstructor(a2);
    struct Minibus* a3 = malloc(sizeof(struct Minibus));
    MConstructor(a3);
    union PTunion *array[] = { a1, a2, a3 };

    for (int i = 0; i < 3; ++i) {
        //array[i]->pt->vtable->display(array[i]->pt);
    }

    for (int i = 0; i < 3; ++i) {
        //array[i]->pt->vtable->Destructor(array[i]->pt);
        free(array[i]);
    }
    
    struct Minibus b1;
    MConstructor(&b1);
    struct Taxi b2;
    TConstructor(&b2);
    struct PublicTransport b3;
    PTConstructor(&b3);
    union PTunion arr2[] = { &b1, &b2, &b3 };

    for (int i = 0; i < 3; ++i) {
        arr2[i].pt->vtable->display(arr2[i].pt);
    }
    M_print_info(arr2[0].mb);

    PrintCount();
    struct Minibus m2;
    MConstructor(&m2);
    PrintCount();

    struct Minibus arr3[4];
    for (int i = 0; i < 4; ++i)
    {
        MConstructor(&arr3[i]);
    }
    struct Taxi *arr4 = malloc (4*sizeof(struct Taxi));
    for (int i = 0; i < 4; ++i)
    {
        TConstructor(&arr4[i]);
    }
    for (int i = 0; i < 4; ++i)
    {
        TDestructor(&arr4[i]);
    }
    free(arr4);

    printf("%d\n", max_func(1, 2));
    printf("%d\n", max_func(1, 2.0f));
    struct SpecialTaxi st;
    STConstructor(&st);
    taxi_display(&st);
    
    struct PublicConvoy *ts1 = malloc(sizeof(struct PublicConvoy));
    PCConstructor(ts1);
    struct PublicConvoy *ts2 = malloc(sizeof(struct PublicConvoy));
    PCCopy(ts2, ts1);
    
    PCDisplay(ts1);
    PCDisplay(ts2);
    PCDestructor(ts1);
    free(ts1);
    PCDisplay(ts2); // this crashes. fix the bug!
    PCDestructor(ts2);
    free(ts2);
    
    STDestructor(&st);
    for (int i = 0; i < 4; ++i)
    {
        MDestructor(&arr3[i]);
    }
    for (int i = 0; i < 3; ++i) {
        arr2[i].pt->vtable->Destructor(arr2[i].pt);
    }
    PTDestructor(&pt);
    MDestructor(&m);
    return 0;
}
