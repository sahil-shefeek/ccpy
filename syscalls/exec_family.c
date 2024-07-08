#include <unistd.h>

// Execl takes in list of args
// int main(int argc, char *argv[], char* envp[]) {
//   execl("/sbin/ping", "/sbin/ping", "google.in", NULL);
//   return 0;
// }

// Execlp takes in list of args and uses $PATH
// int main(int argc, char *argv[], char* envp[]) {
//   execlp("ping", "ping", "google.in", NULL);
//   return 0;
// }

// Execv takes in vector of args
// int main(int argc, char *argv[], char* envp[]) {
//   char *arg_vector[] = {"/sbin/ping", "google.in", NULL};
//   execvp("/sbin/ping", arg_vector);
//   return 0;
// }

// Execvp takes in vector of args and uses $PATH
// int main(int argc, char *argv[], char* envp[]) {
//   char *arg_vector[] = {"ping", "google.in", NULL};
//   execvp("ping", arg_vector);
//   return 0;
// }

// Execve takes in vector of args and an environment.
int main(int argc, char *argv[], char *envp[]) {
  char *arg_vector[] = {"/sbin/ping", "google.in", NULL};
  char *env[] = {"TEST_ENV_VAR=1", NULL};
  execve("/sbin/ping", arg_vector, env);
  return 0;
}
