#ifndef _SERVICE_H_
#define _SERVICE_H_

/******************************** INCLUDE FILES *******************************/
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*********************************** DEFINES **********************************/

/*********************************** TYPEDEFS *********************************/
typedef struct _service_t service_t;

/*************************** SERVICE METHODS **********************************/

service_t *
service_new(const char *);

void
service_destroy(service_t **);

void service_connection_cb(int, void *);

#ifdef __cplusplus
}
#endif
#endif /* _SERVICE_H_ */
