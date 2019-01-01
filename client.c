#include <signal.h>
#include "pipe_networking.h"

static void sighandler(int signo) {

  printf("\n\nGoodbye!\n");
  exit(EXIT_SUCCESS);

}

int main() {

  signal(SIGINT, sighandler);
  
  int to_server; // write
  int from_server; // read

  from_server = client_handshake( &to_server );

  char buffer[BUFFER_SIZE];
  
  while (1)
    {
      // get input from stdin
      printf("[client] says: ");
      fflush(stdout);
      //fgets(buffer, BUFFER_SIZE, stdin);
      fscanf(stdin, "%s", buffer);
      
      // give that input to server
      // CHANGE THIS TO HANDLE IF CLIENT CUTS OFF
      if ( !write(to_server, buffer, BUFFER_SIZE) )
	{
	  printf("\nGoodbye!\n");
	  exit(EXIT_SUCCESS);
	}
      
      // get response from server
      if ( !read(from_server, buffer, BUFFER_SIZE) )
	{
	  printf("\nGoodbye!\n");
	  exit(EXIT_SUCCESS);
	}

      // display that
      printf("[client] received: %s", buffer);
    }
}
