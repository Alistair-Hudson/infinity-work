#ifndef __UID_OL85_H__
#define __UID_OL85_H__

/*******************************************************************************
                                 *  OL85 API
                                 * version 23.02.2020.1
 ******************************************************************************/

#include <stddef.h> /* size_t */
#include <time.h> /* time_t */
#include <unistd.h> /* pid_t */
#include <sys/types.h> /* pid_t */
#include <pthhread.h>	/* pthread functions */
typedef struct
{
    time_t timestamp;
    pid_t pid;
    size_t counter;
} ilrd_uid_t;

/*
 * When UIDCreate fails, returns an invalid UID, that can be compared using the
 * the UIDIsSame function and the following bad_uid.
 */
extern ilrd_uid_t bad_uid;

/*
 * Input: (void)
 * Process: Create a new UID
 * Return: An uid_t by vale. If it fails returns an invalid UID that can be
 * check with the UIDIsSame function and the provided bad_uid.
 */
ilrd_uid_t UIDCreate(void);

/*
 * Input: Two uid_t UID
 * Process: Compares two given UIDs
 * Return: 1 if are the same and 0 if they are not.
 */
int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

#endif /* __UID_OL85_H__ */
