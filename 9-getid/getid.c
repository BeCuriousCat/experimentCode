#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
int main(int argc ,char **argv ){

	pid_t my_pid,parent_pid;
	uid_t my_uid,my_euid;
	gid_t my_gid,my_egid;
	struct passwd *my_info;
	my_pid = getpid();
	parent_pid = getppid();
}
