#include "event.hh"
std::ifstream jsonfile("../world/Story.json");
nlohmann::json Story = nlohmann::json::parse(jsonfile);

void MoveFlagsIntoQueue(std::vector<const Flag*>& input, std::vector<const Flag*>& output){
  for(const auto& i : input){
    output.push_back(i);
  }
}
void Event::SortAndPopulateQueue(const std::vector<Flag>& compare){
  short count = 0;
  std::vector<const Flag*> HighestFlags;
  std::vector<const Flag*> HighFlags;
  std::vector<const Flag*> NormalFlags;
  std::vector<const Flag*> LowFlags;
  std::vector<const Flag*> LowestFlags;
  for(auto& i : compare){
    const Flag* itr = &i;
    if(!itr->tag.compare(compare[count].tag)){ 
      switch(itr->weight){
      case PRIORITY_LEVEL::HIGHEST:
	HighestFlags.push_back(itr);
	break;
      case PRIORITY_LEVEL::HIGH:
	HighFlags.push_back(itr);
	break;
      case PRIORITY_LEVEL::NORMAL:
	NormalFlags.push_back(itr);
	break;
      case PRIORITY_LEVEL::LOW:
	LowFlags.push_back(itr);
	break;
      case PRIORITY_LEVEL::LOWEST:
	LowestFlags.push_back(itr);
	break;
      }
    }
    count++;
  }
  MoveFlagsIntoQueue(HighestFlags, FlagQueue);
  MoveFlagsIntoQueue(HighFlags, FlagQueue);
  MoveFlagsIntoQueue(NormalFlags, FlagQueue);
  MoveFlagsIntoQueue(LowFlags, FlagQueue);
  MoveFlagsIntoQueue(LowestFlags, FlagQueue);
}
        
    
std::string Event::FlagSelector(const std::vector<Flag>& compare={}){
  if(!FlagQueue.empty()){
    std::string SelectedFlag = FlagQueue.front()->tag;
    FlagQueue.erase(FlagQueue.begin());
    return SelectedFlag;
  }
  if(DeleteInitialFlag){
    std::string InitialFlag = FlagList[0].tag;        
    if(!InitialFlag.compare("INITIAL FLAG")){
      FlagList.erase(FlagList.begin()); 
      DeleteInitialFlag = false; 
      return InitialFlag;}
  }
  if(!compare.empty()){
    FlagQueue.clear();
    SortAndPopulateQueue(compare);
    return FlagSelector();
  }
  else{
    std::string InitialFlag = FlagList[0].tag;        
    if(!InitialFlag.compare("INITIAL FLAG")){
      std::string SelectedFlag = FlagList[0].tag;
      return SelectedFlag;
    }
    std::string SelectedFlag = FlagList[1].tag;
    return SelectedFlag;
  }
    
}
void Event::ExtractStoryFromFile(){
  std::string iffy = "/"+std::to_string(x_coordinate)+"/"+std::to_string(y_coordinate)+"/"+FlagSelector();
  nlohmann::json::json_pointer poinr(iffy);
  EventText = Story.at(poinr);
}

void Event::DisplayEvent(){
  ExtractStoryFromFile();
  std::cout << EventText << "\n";
}
void Event::SetFlags(std::string &flag){FlagList.push_back(Flag(flag));}

void Event::SetFlagWeight(const std::string &flag, PRIORITY_LEVEL weight){
  for(auto& i : FlagList){
    if(!i.tag.compare(flag)){
      i.weight = weight;
    }
    FlagQueue.clear();
    SortAndPopulateQueue(FlagList); //might have to change this to make the generator
  }
}

        
