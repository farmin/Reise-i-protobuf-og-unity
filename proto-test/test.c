
#include "test-proto3.pb-c.h"
#include "message.pb-c.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PROTO3

typedef struct pointers_struct{
    uint32_t * a;
    uint32_t * b;
    char * chr_ptr;
    char * msg_ptr_list[10];   
    char ** msg_ptr;


}pointers_p;

uint8_t message_with_pointer(struct _Test__Message * message,
			     struct pointers_struct * pointers)
{
    uint32_t a = 32;
    uint32_t b = 33;
    char test[] = "happy times når det virkelig gjelder";
    pointers->chr_ptr = (char *)malloc(sizeof(test));
    memcpy(pointers->chr_ptr, test, sizeof(test));
    message->a = a;
    message->b = b;
    message->test = pointers->chr_ptr;
    return 0;
}

uint8_t repeated_message_with_pointers(struct _Test__RepeatedMessage * repeated_message,
				       struct _Test__Message * message[],
				       struct pointers_struct * pointers)
{
    char test2[] = "happy times når det snør";
    char test[] = "happy times når det virkelig gjelder";
    pointers->msg_ptr[0] = (char *)malloc(sizeof(test2));
    memcpy(pointers->msg_ptr[0], test2, sizeof(test2));
    uint8_t message_number = 0;
    repeated_message->n_message = message_number;
    repeated_message->message = malloc(sizeof(message[0])* 10);
    repeated_message->message[message_number] = message[message_number]; 
    size_t size = 0;
    

    
    size = sizeof(**message)/sizeof(* message);
    for (uint32_t i = 0; i < size; ++i)
    	{
    	    message[i] = malloc(150);
    	    repeated_message->message[i] = message[i];
	    message[i]->a = i + 1;
	    message[i]->test = malloc(sizeof(test));
	    memcpy(message[i]->test, test, sizeof(test));

    	    /* pointers->msg_ptr[i] = (char *)malloc(sizeof(test2)); */
    	    //memcpy(pointers->msg_ptr[i], test2, sizeof(test2));
    	    //message[i]->test = pointers->msg_ptr[i];
    	}
    //repeated_message->n_message = size;
    printf("i : %li\n",size);
    
    
    
    return 0;
}

#define LIST_LEN 10
#define MESSAGE_NMESG 5
int main(void)
{
  Foo__Person__PhoneNumber__Comment comment = FOO__PERSON__PHONE_NUMBER__COMMENT__INIT;
  Foo__Person__PhoneNumber phone = FOO__PERSON__PHONE_NUMBER__INIT;
  Foo__Person__PhoneNumber *phone_numbers[1];
  Foo__Person person = FOO__PERSON__INIT;
  Foo__Person *person2;
  unsigned char simple_pad[8];
  size_t size, size2;
  unsigned char *packed;
  ProtobufCBufferSimple bs = PROTOBUF_C_BUFFER_SIMPLE_INIT (simple_pad);

  Test__Message message = TEST__MESSAGE__INIT;

  Test__Message * many_messages[5];
  many_messages[0] = &message;
  many_messages[1] = &message;
  many_messages[2] = &message;
  many_messages[3] = &message;
  many_messages[4] = &message;
  many_messages[5] = &message;
  
  pointers_p pointers;

  /* char * lptr[10]; */
  /* pointers.msg_ptr = &lptr[0]; */

  Test__RepeatedMessage repeated = TEST__REPEATED_MESSAGE__INIT;
  pointers.msg_ptr = (char **)malloc(LIST_LEN*sizeof(char));

  char test2[] = "happy times når det snør";

  pointers.msg_ptr[0] = (char *)malloc(sizeof(test2));
  memcpy(pointers.msg_ptr[0], test2, sizeof(test2));

  printf("*.msg_ptr[0] is   : %s\n", pointers.msg_ptr[0]);
  

  
  repeated.n_message = 5;
  repeated.message = malloc(sizeof(message));
  repeated.message[0] = &message;

  
  repeated_message_with_pointers(&repeated,
  				 many_messages,
  				 &pointers);
  
  message_with_pointer(&message, &pointers);


  printf("repeated.message  : %s\n", repeated.message[0]->test);
  printf("message.a is      : %i\n", message.a);
  printf("message.test is   : %s\n", message.test);
  printf("sizeof message.test: %lu\n", (sizeof(message.test) * sizeof(message.test[0])));
  for(int i = 0; i < (38) +1 ; ++i){
      printf("%c", message.test[i]);
  }
  printf("\n");
  int i = 0;
  for(i = 0; i < 5; i++)
      {
	  printf("%i", i);
	  printf("repeated.message %i : %i\n",i ,repeated.message[i]->a);
	  printf("repeated.message %i : %s\n",i ,repeated.message[i]->test);
      }
  free(pointers.chr_ptr);
  printf("free(pointers.chr_: %s\n", message.test);
  
  comment.comment = "protobuf-c guy";
  phone.number = "1234";
#ifndef PROTO3
  phone.has_type = 1;
#endif
  phone.type = FOO__PERSON__PHONE_TYPE__WORK;
  phone.comment = &comment;

  phone_numbers[0] = &phone;

  person.name = "dave b";
  person.id = 42;
  person.n_phone = 1;
  person.phone = phone_numbers;

  size = foo__person__get_packed_size (&person);
  packed = malloc (size);
  assert (packed);

  size2 = foo__person__pack (&person, packed);

  assert (size == size2);
  foo__person__pack_to_buffer (&person, &bs.base);
  assert (bs.len == size);
  assert (memcmp (bs.data, packed, size) == 0);

  PROTOBUF_C_BUFFER_SIMPLE_CLEAR (&bs);

  person2 = foo__person__unpack (NULL, size, packed);
  assert (person2 != NULL);
  assert (person2->id == 42);
#ifndef PROTO3
  assert (person2->email == NULL);
#else
  assert (strcmp (person2->email, "") == 0);
#endif
  assert (strcmp (person2->name, "dave b") == 0);
  assert (person2->n_phone == 1);
  assert (strcmp (person2->phone[0]->number, "1234") == 0);
  assert (person2->phone[0]->type == FOO__PERSON__PHONE_TYPE__WORK);
  assert (strcmp (person2->phone[0]->comment->comment, "protobuf-c guy") == 0);

  foo__person__free_unpacked (person2, NULL);
  free (packed);

  printf ("test succeeded.\n");

  return 0;
}
