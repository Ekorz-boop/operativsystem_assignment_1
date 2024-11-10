


/*
Implement Dining Professors with five professors according to the description above. The program shall contain five
threads, where each thread represents one professor. The program must guarantee that only one professor at the time can
use a chopstick.
• Let the professors think a random time between one and five seconds.
• Take the left chopstick.
• When they have gotten the left chopstick, let them think in two to eight seconds.
• Take the right chopstick.
• Let the professor eat for a random time between five-ten seconds, and then put down both chopsticks.
• Write information to the terminal when the professors go from one state to another, e.g., "Tanenbaum: thinking ->
got left chopstick". Also indicate when a professor tries to take a chopstick.
There are some restrictions for your implementation.
• Each fork should be modeled as a shared resource, which exclusive usage.
• You are not allowed to look at the state of your neighbors to see if they are eating or not, i.e., the solution in Section
2.5.1 in the course book [2] is not allowed.
*/