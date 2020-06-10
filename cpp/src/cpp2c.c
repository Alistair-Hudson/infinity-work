#include <stdio.h>


/*===PUBLIC TRANSPORT CLASS===*/
static int s_count = 0;
/*class PublicTransport {
public:
protected:
    int get_ID()
    {
        return m_license_plate;
    }
};
int PublicTransport::s_count = 0;*/
struct PublicTransport;

struct VTable_PublicTransport
{
    void (*Deconstructor)(struct PublicTransport*);
    void (*display)(struct PublicTransport*);
};

struct PublicTransport
{
    struct VTable_PublicTransport* v_ptr;
    int m_license_plate;
};

void PublicTransport_Deconstuctor(struct PublicTransport* p_this)
{
    printf("PublicTransport::Dtor() %d\n", p_this->m_license_plate);
}

void PublicTransport_Display(struct PublicTransport* p_this)
{
    printf("PublicTransport::Display() %d\n", p_this->m_license_plate);
}

struct VTable_PublicTransport g_VTable_PublicTransport = {PublicTransport_Deconstuctor, PublicTransport_Display};

void PublicTransport_Constuctor(struct PublicTransport* p_this)
{
    p_this->v_ptr = &g_VTable_PublicTransport;
    p_this->m_license_plate = ++s_count;
    printf("PublicTransport::Ctor() %d\n", p_this->m_license_plate);
}

void PublicTransport_CConstuctor(struct PublicTransport* p_this, struct PublicTransport* other)
{
    p_this->v_ptr = &g_VTable_PublicTransport;
    p_this->m_license_plate = other->m_license_plate;
    printf("PublicTransport::CCtor() %d\n", p_this->m_license_plate);
}

static void PublicTransport_print_count()
{
    printf("s_count: %d\n", s_count);
}

int PublicTransport_id(struct PublicTransport* p_this)
{
    return p_this->m_license_plate; 
}

/*===Minibus Class===*/
struct Minibus;

struct VTable_Minibus
{
    void (*wash)(struct Minibus* p_this, int minutes);
};

struct Minibus
{
    struct PublicTransport base_class;
    struct VTable_Minibus* v_ptr;
    int m_numSeats;
};

void Minibus_Wash(struct Minibus* p_this, int minutes)
{
    printf("Minibus::wash(%d) ID: %d", minutes, PublicTransport_id(&p_this->base_class));
}

struct VTable_Minibus g_VTable_Minibus = {Minibus_Wash};

void Minibus_Constructor(struct Minibus* p_this)
{
    PublicTransport_Constuctor(&p_this->base_class);
    p_this->v_ptr = &g_VTable_Minibus;
    p_this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void Minibus_CConstructor(struct Minibus* p_this, struct Minibus* other)
{
    PublicTransport_CConstuctor(&p_this->base_class, &other->base_class);
    p_this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void Minibus_Deconstructor(struct Minibus* p_this)
{
    printf("Minibus::Dtor()\n");
    PublicTransport_Deconstuctor(&p_this->base_class);
}

void Minibus_Display(struct Minibus* p_this)
{
    printf("Minibus::display() ID: %d", PublicTransport_id(&p_this->base_class));
    printf("num seats: %d", p_this->m_numSeats);
}

/*===Taxi Class===*/
struct Taxi
{
    struct PublicTransport base_class;
};

void Taxi_Constructor(struct Taxi* p_this)
{
    PublicTransport_Constuctor(&p_this->base_class);
    printf("TAxi::Ctor()\n");
}

void Taxi_CConstructor(struct Taxi* p_this, struct Taxi* other)
{
    PublicTransport_CConstuctor(&p_this->base_class, &other->base_class);
    printf("Taxi::CCtor()\n");
}

void Taxi_Deconstructor(struct Taxi* p_this)
{
    printf("Taxi::Dtor()\n");
    PublicTransport_Deconstuctor(&p_this->base_class);
}

void Taxi_Display(struct Taxi* p_this)
{
    printf("Taxi::display() ID: %d", PublicTransport_id(&p_this->base_class));
}

/*===T Class===*/

/*===Special Taxi Class===*/
struct SpecialTaxi
{
    struct Taxi base_class;
};

void SpecialTaxi_Constructor(struct SpecialTaxi* p_this)
{
    Taxi_Constuctor(&p_this->base_class);
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxi_CConstructor(struct SpecialTaxi* p_this, struct SpecialTaxi* other)
{
    Taxi_CConstuctor(&p_this->base_class, &other->base_class);
    printf("Taxi::CCtor()\n");
}

void SpecialTaxi_Deconstructor(struct SpecialTaxi* p_this)
{
    printf("SpecialTaxi::Dtor()\n");
    Taxi_Deconstuctor(&p_this->base_class);
}

void SpecialTaxi_Display(struct SpecialTaxi* p_this)
{
    printf("SpecialTaxi::display() ID: %d", PublicTransport_id(&p_this->base_class.base_class));
}

/*===Other Functions===*/
void PT_print_info(struct PublicTransport* a)
{
    a->v_ptr.display(a);
}

void V_print_info(void)
{
    PublicTransport_print_count();
}

void M_print_info(struct Minibus* m)
{
    m->v_ptr.wash(m, 3);
}

struct PublicTransport I_print_info(int i)
{
    struct Minibus ret;
    Minibus_Constructor(&ret);
    printf("print_info(int i)\n");
    Minibus_display(&ret);
    return ret.base_class;
}

void taxi_display(struct Taxi* s)
{
    Taxi_display(s);
}

/*===Main===*/
int main(int argc, char **argv, char **envp)
{
    struct Minibus m;
    Minibus_Constructor(&m);
    M_print_info(&m);
    I_print_info(3).v_ptr.display();
    struct PublicTransport *array[] = { new Minibus(), new Taxi(), new Minibus() };

    for (int i = 0; i < 3; ++i) {
        array[i]->display();
    }

    for (int i = 0; i < 3; ++i) {
        delete array[i];
    }

    struct PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };

    for (int i = 0; i < 3; ++i) {
        arr2[i].v_ptr.display();
    }
    print_info(arr2[0]);

    PublicTransport_print_count();
    struct Minibus m2;
    Minibus_Constructor(&m2);
    PublicTransport_print_count();

    struct Minibus arr3[4];
    struct Taxi *arr4 = new Taxi[4];
    delete[] arr4;

    std::cout << max_func(1, 2) << "\n";
    std::cout << max_func<int>(1, 2.0f)<< "\n";
    SpecialTaxi st;
    taxi_display(st);

    /*PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;*/

    return 0;
}

