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

typedef void (*service_conn_cb_t)(int, void *);
/*************************** SERVICE METHODS **********************************/

service_t *
service_new(const char *);

void
service_destroy(service_t **);

service_conn_cb_t
service_conn_cb(service_t *);

#ifdef __cplusplus
}
#endif
#endif /* _SERVICE_H_ */
