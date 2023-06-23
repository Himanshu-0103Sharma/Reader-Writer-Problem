# Reader-Writer-Problem
Reader Writer Process Synchronization Problem with busy wait solution

Psedocode of The Reader-Writer Problem

The structure of Writer Process:
while (true) {
  wait(rw mutex);
  ...
  /* writing is performed */
  ...
  signal(rw mutex);
}

The structure of Reader Process:
while (true) {
  wait(mutex);
  read count++;
  if (read count == 1)
    wait(rw mutex);
  signal(mutex);
  ...
  /* reading is performed */
  ...
  wait(mutex);
  read count--;
  if (read count == 0)
    signal(rw mutex);
  signal(mutex);
}
