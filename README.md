# Philosophers 🍽

The goal of this project was to use mutexes. 

## Rules:
- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
- While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

## Usage
1. Clone repository
2. Move to directory
```bash
cd Philosophers/philo
```
3.Run make file
```bash
make
```
4. Run th program : example
   
```bash
./philo 1 800 200 200
```
### Expected output:
```
has died
```
***OR***
```bash
./philo 5 800 200 200
```
### Expected output:
Will not stop programm at all

***OR***
```bash
./philo 5 800 200 200 7 | grep ....
```
### Expected output:
everyone need to eat 7 times

