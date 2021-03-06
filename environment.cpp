#include "environment.h"
#include "utils.h"
#include <sstream>
#include <utility>
using namespace std;

#define BASESTATION_1_X 0
#define BASESTATION_1_Y 0
#define BASESTATION_2_X 0
#define BASESTATION_2_Y 999
#define BASESTATION_3_X 999
#define BASESTATION_3_Y 500

void Environment::initialization(string _chromosome, bool _verbose, int seed)
{
    verbose       = _verbose;
    chromosome    = string(_chromosome.c_str());
    step_count    = 0;
    phone_number  = 0;
    phone_next_id = 1;
    data_sent     = 0.0;

    //Initialize the random generator.
    srand(seed);

    basestation_list[0] =
      new Basestation(BASESTATION_1_X, BASESTATION_1_Y, chromosome);
    basestation_list[1] =
      new Basestation(BASESTATION_2_X, BASESTATION_2_Y, chromosome);
    basestation_list[2] =
      new Basestation(BASESTATION_3_X, BASESTATION_3_Y, chromosome);

    ostringstream output_file_name;
    output_file_name << "results_" << seed << ".txt";
    output_file.open(output_file_name.str().c_str(), fstream::out);
}

vector<pair<int, int> > Environment::get_basestation_positions(){
  vector<pair<int, int> >ret;
  for (int i = 0; i < MAX_BASESTATIONS; i++){
    ret.push_back(make_pair(basestation_list[i]->get_x(),
                            basestation_list[i]->get_y()));
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
  return chromosome.c_str();
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

     // Physical constants.
     const double lambda = 1.0;           // wavelength
     const double alpha = 3.0;            // exponent attenuation TODO (?)
     const double P_t = 10;               // emitting power
     const double gamma = 10;             // random distribution - shadowing TODO (?)
     const double bandwith_width = 1000;  // bandwith width TODO (?)
     const double k = 1.38065812e-23;     // Boltzman constant.
     const double T = 300;                // Temperature (300K = 25c)
     const double W = 1000;               // receiver bandwith width TODO (?)

    // Received power base calculation.
    const double P_0 = pow(4 * M_PI / lambda, 2);
    double P_r = P_t * P_0 * gamma * pow(1 / distance, alpha);

    // Calculate interference TODO
    double P_i = 0;

    // Calculate noise
    double P_n = k * W * T;

    // Calculate SINR
    double SINR = P_r / (P_n + P_i);
    double R = bandwith_width * log2(1.0 + SINR);

    data_sent += R;
}
