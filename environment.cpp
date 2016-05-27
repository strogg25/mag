#include "environment.h"
#include "utils.h"
#include <sstream>

void Environment::initialization(string _chromosome, bool _verbose, int seed)
{
    verbose       = _verbose;
    chromosome    = _chromosome;
    step_count    = 0;
    phone_number  = 0;
    phone_next_id = 1;
    data_sent     = 0.0;

    basestation_list[0] = new Basestation(0,0, (void*)this);
    basestation_list[1] = new Basestation(0,999, (void*)this);
    basestation_list[2] = new Basestation(999, 500, (void*)this);

    //Initialize the random generator.
    srand(seed);

    ostringstream output_file_name;
    output_file_name << "results_" << seed << ".txt";
    output_file.open(output_file_name.str().c_str(), fstream::out);
}

vector<pair<int, int> > Environment::get_basestation_positions(){
  vector<pair<int, int> >ret;
  for (int i = 0; i < MAX_BASESTATIONS; i++){
    ret.push_back(make_pair(basestation_list[i]->get_x(), basestation_list[i]->get_y()));
  }
  return ret;
}

void Environment::info(string s){
  if (verbose)
    printf("%s", s.c_str());

  output_file << s;
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
        ostringstream communicate;
        communicate << "Max phones reached. skipping." << endl;
        info(communicate.str());
      } else {
        Phone *phone = new Phone(x,y,priority, ID, (void*)this);
        if (phone->get_assigned_basestation() == -1){
          ostringstream communicate;
          communicate << "Can't create a phone." << endl;
          info(communicate.str());
        }
        else{
          phone_list[phone_number++] = phone;
          ostringstream communicate;
          communicate << "Phone created at (" << x << ", " << y
            << ") with priority " << priority << " and ID " << ID << endl;
          info(communicate.str());
        }
      }
    }

    //The event of a phone disconnection.
    if (phone_number > 0 && (rand() % 100 < PHONE_DISCONNECT)){
        int id = rand() % phone_number;
        Phone* handle = phone_list[id];
        ostringstream communicate;
        communicate << "Phone with ID " << handle->get_id()
        << " disconnected" << endl;
        info(communicate.str());
        delete handle;
        phone_list[id] = phone_list[phone_number-1];
        phone_number--;
    }

    //Data transmission
    for(int i = 0; i < phone_number; i++){
      Phone *phone = phone_list[i];
      phone->send_data();
    }
}

Basestation* Environment::get_basestation(int id){
  return basestation_list[id];
}

string Environment::get_chromosome(){
  return chromosome;
}

void Environment::main_loop()
{
    while(step_count < MAX_STEP){
      step();
    }
    ostringstream communicate;
    communicate << "=== SUMMARY ===" << endl
    << "Created phones: " << phone_next_id
    << " Remaining phones: " << phone_number
    << " Data sent: " << data_sent << endl;
    info(communicate.str());
}

void Environment::send_data(int phone_x, int phone_y,
                            int basestation_x, int basestation_y,
                            int bandwith){
    double distance = Utils::get_distance(phone_x, phone_y,
                                       basestation_x, basestation_y);

    // Received power base calculation
    const double lambda = 1.0;
    const double g_r = 16;
    const double g_t = 2;
    const double P_t = 10;

    double denominator = (4 * M_PI * distance);
    double P_r = P_t * (lambda * lambda * g_r * g_t);
    P_r /=          (denominator * denominator);

    // Calculate shadowing TODO
    // Calculate interference TODO
    // Calculate noise TODO
    // Calculate SINR TODO

    data_sent += P_r;

}
