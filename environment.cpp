#include "environment.h"

void Environment::initialization()
{
    step_count    = 0;
    phone_number  = 0;
    phone_next_id = 0;

    basestation_list[0] = new Basestation(0,0);
    basestation_list[1] = new Basestation(0,999);
    basestation_list[2] = new Basestation(999, 500);
}

vector<pair<int, int> > Environment::get_basestation_positions(){
  vector<pair<int, int> >ret;
  for (int i = 0; i < MAX_BASESTATIONS; i++){
    ret.push_back(make_pair(basestation_list[i]->get_x(), basestation_list[i]->get_y()));
  }
  return ret;
}

void Environment::step()
{
    step_count++;
    //printf("Step %d\n", step_count);

    //The event of a new phone creation.
    if ((rand() % 100) < NEW_PHONE_CHANCE){

      //Randomly selecting the parameters
      int x = rand() % 1000;
      int y = rand() % 1000;
      int priority = rand() % 2;
      int ID = phone_next_id++;

      //Adding a new phone to the list
      if (phone_number >= MAX_PHONES){
        printf("Max phones reached. skipping");
      } else {
        Phone *phone = new Phone(x,y,priority, ID, get_basestation_positions());
        phone_list[phone_number++] = phone;
        printf("Phone created at (%d, %d) with priority %d and ID %d \n", x,y,priority, ID);
      }
    }

    //The event of a phone disconnection.
    if (phone_number > 0 && (rand() % 100 < PHONE_DISCONNECT)){
        int id = rand() % phone_number;
        Phone* handle = phone_list[id];
        printf("Phone with ID %d disconnected\n", handle->get_id());
        delete handle;
        phone_list[id] = phone_list[phone_number-1];
        phone_number--;
    }
}

void Environment::main_loop()
{
    while(step_count < MAX_STEP){
      step();
    }
    printf("SUMMARY: \n");
    printf("Created phones: %d. Remaining phones: %d\n", phone_next_id, phone_number);
}
