//#include "llqueue.h"
#include "arrqueue.h"
#include <stdio.h>

#define NUM_DOCTORS 2
#define NUM_PRIORITIES 5

int SERVICE_TIMES[] = {2, 2, 5, 10, 20};

doctor doctors[NUM_DOCTORS];
QUEUE *patient_queues[NUM_PRIORITIES];

void init_doctors() {
	int i;
	for(i = 0; i < NUM_DOCTORS; i++) {
		doctors[i].time_remaining = 0;
		doctors[i].doctor_id = i;
		doctors[i].patient_serviced.patient_id = -1;
	}
}

void init_queues() {
	int i;
	for(i = 0; i < NUM_PRIORITIES; i++)
		patient_queues[i] = newqueue();
}

int read_patient(patient *curr_patient) {
	char c;
	char line[100];
	int i = 0;

	while((c = getchar()) != '\n' && c != EOF) {
		line[i] = c;
		i++;
	}
	if(i == 0)
		return 0;

	line[i] = '\n';
	sscanf(line, "%d %d %[^\n]s", &(curr_patient->patient_id), 
		&(curr_patient->priority), 
		curr_patient->name);
	curr_patient->arrival_time = -1;
	curr_patient->service_time = -1;
	return 1;
}

void display_patient(char prefix[30], patient *curr_patient) {
	printf("%s: %s, id %d, priority %d, arrival %d, service %d\n", prefix, 
			curr_patient->name, curr_patient->patient_id, curr_patient->priority,
			curr_patient->arrival_time, curr_patient->service_time);
}

void main() {
	init_doctors();
	init_queues();
	int clock_tick = 0, i, j, doctors_idle = 1, new_patient;
	patient curr_patient;

	float waiting_time_sum[NUM_PRIORITIES];
	int waiting_patients[NUM_PRIORITIES];
	for(i = 0; i < NUM_PRIORITIES; i++) {
		waiting_time_sum[i] = 0;
		waiting_patients[i] = 0;
	}

	while((new_patient = read_patient(&curr_patient)) || doctors_idle == 0) {
		if(new_patient == 1) {
			curr_patient.arrival_time = clock_tick;
			display_patient("Arrived", &curr_patient);
			enqueue(patient_queues[curr_patient.priority], curr_patient);
		}

		doctors_idle = 1;
		for(i = 0; i < NUM_DOCTORS; i++) {
			if(doctors[i].time_remaining > 0) {
				doctors[i].time_remaining--;
				printf("Doctor %d working on %s, %d\n", i, doctors[i].patient_serviced.name, 
					doctors[i].time_remaining);
				doctors_idle = 0;
			}
			else {
				for(j = NUM_PRIORITIES-1; j >= 0; j--) {
					if(queue_length(patient_queues[j]) > 0) {
						curr_patient = dequeue(patient_queues[j]);
						curr_patient.service_time = clock_tick;
						display_patient("Servicing", &curr_patient);

						doctors[i].time_remaining = SERVICE_TIMES[curr_patient.priority];
						doctors[i].patient_serviced = curr_patient;
						printf("     assigned to doctor %d, for %d\n", i,
							doctors[i].time_remaining);
						doctors_idle = 0;

						waiting_time_sum[j] += (curr_patient.service_time -
									curr_patient.arrival_time);
						waiting_patients[j]++;

						break;
					}
				}
			}
		}

		clock_tick++;
	}

//	for(i = 0; i < NUM_PRIORITIES; i++) {
//		printf("%d num patients %d\n", i, queue_length(patient_queues[i])); 
//		while(!is_empty(patient_queues[i])) {
//			curr_patient = dequeue(patient_queues[i]);
//			display_patient("End - dequeued", &curr_patient);
//		}
//	}

	for(i = 0; i < NUM_PRIORITIES; i++) {
		printf("priority %d, patients services %d, avg waiting time %f\n", i, 
			waiting_patients[i], waiting_time_sum[i] / waiting_patients[i]);
	}
}
