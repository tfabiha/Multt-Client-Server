#include <signal.h>
#include "pipe_networking.h"

static void sighandler(int signo) {

  remove("client_write");
  exit(EXIT_SUCCESS);
}

int main() {

  signal(SIGINT, sighandler);

  int main_server = getpid();
  
  int to_client; // write
  int from_client; // read

  char buffer[BUFFER_SIZE];

  while (1)
    {
      if (getpid() == main_server)
	{
	  from_client = server_handshake( &to_client );
	}
      else
	{
	  if ( !read(from_client, buffer, BUFFER_SIZE) ) // if you can't read
	    {
	      exit(0);
	    }
	  else // if you can read
	    {
	      // process the data
	      printf("[server-child %d] received: %s\n", getpid(), buffer);
	    
	      strncat(buffer, ", i like that\n", BUFFER_SIZE);
	  
	      //reply to client
	      write(to_client, buffer, BUFFER_SIZE);
	    }
      
	}
	  
	}

}
