# Vineyard-Simulation
This is a task from Operating System Course at ELTE


Spring is also knocking at the door of the "Drink my friend" vineyard. As we all know, grapes love care and work, but most of all they love to work, which is usually rewarded with a good harvest. The vineyard needs a lot of helpers, so an application is being prepared for those who apply for the job.

Applications are invited from those who can work during the weeks of the spring season. The data is available in a file and any changes can be made.

"Drink my friend" vineyard (parent process) each morning will review the applications and needs for the day and start the worker process(es) for the day (child process(es)) Only a small bus is available that can carry a maximum of 5 people and there are two buses only. (The vineyard is a small company, so no more than 10 workers per day are needed.) The vineyard starts the minibus(es), who, when ready to go, send a signal back to the parent, and then receive the name list of workers as a reply via pipe from the vineyard. This information is also written on the screen by the child process (bus). As soon as the workers have been brought in, a summary message via message queue, is sent back to the vineyard, indicating how many of the requested workers have been brought in. This is written to the screen by the vineyard and then they terminate. The parent waits for the end of the child process and is ready to organise the next day's worker shuttle. (They can add or modify another applicant or start another day's bus run.)

