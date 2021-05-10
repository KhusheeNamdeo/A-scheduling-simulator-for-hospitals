#define DTYPE patient

typedef struct {
	int patient_id;
	int priority;
	int arrival_time;
	int service_time;
	char name[30];
} patient;

typedef struct {
	int time_remaining;
	int doctor_id;
	patient patient_serviced;
} doctor;

//#define QUEUE llqueue
#define QUEUE arrqueue
