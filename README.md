# A-scheduling-simulator-for-hospitals

We will first build a workload generator that takes the given parameters as input and generates a sample traffic for the simulator.
"workloadgen.c" does the job.
 We have two entities, patients and doctors. 
 Whenever a patient arrives, we first have to look at the priority for that patient, and then assign the patient to wait alongside other patients with the same priority level.
 For each doctor, we will have to keep track of when the doctor becomes free. And whenever a doctor becomes free, we should assign a patient to that doctor --
 this patient should be picked up from among the highest priority patients who are waiting, if there are no highest priority patients then from the next lower priority, and so on.
 We therefore have to maintain the set of patients for each priority level, keep adding patients to the appropriate priority level as they arrive, and remove patients one by one
 from their set starting from the earliest patient who arrived for that set.
