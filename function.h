#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <langinfo.h>
#define TOKEN_BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"
#define CMD_DELIM ";\n"
#define LSH_RL_BUFSIZE 1024
int max;
int jobs(char **args);
void back_process(int pid, char *str);
int set_env(char **args);
int unset_env(char **args);
int cd(char **args);
int pwd(char **args);
int echo(char **args);
int ls(char **args);
int pinfo(char **args);
int lsl(char **args);
int fclock(char **args);
int print_prompt();
int quit(char **args);
void sigstop(int sig_num);
char **split_pipe_fxn(char *line);
void loop();
int execute_func(char **args);
int launch_func(char **args);
void sigh(int signum);
char **split_cmd_fxn(char *line);
char **split_line_fxn(char *line);
char *read_line(void);
void background_fxn();
void SIGINT_handler(int sig);
void SIGQUIT_handler(int signal_num);
void SIGTSTP_handler(int signal_num);
char *Get_Current_Directory();
int overkill(char **args);
int kjob(char **args);
int pipe_fxn(char **args);
int redirect_fxn(char **args);
int bg(char **args);
int fg(char **args);

static char perms_buff[30];

char home[1111];
char previous[1111];
typedef struct curr_job
{
	int state;
	int pid;
	int jobid;
	char *command;
} curr_job;

curr_job backgrund_process[111];
