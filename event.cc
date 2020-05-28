#include "event.hh" 
std::ifstream jsonfile("../world/_story.json"); 
nlohmann::json _story = nlohmann::json::parse(jsonfile); 
void _move_flags_into_queue(std::vector<const _flag*>& input, std::vector<const _flag*>& output){ 
for(const auto& i : input){ 
output.push_back(i); 
} 
} 
void _event::_sort_and_populate_queue(const std::vector<_flag>& compare){ 
short count = 0; 
std::vector<const _flag*> _highest_flags; 
std::vector<const _flag*> _high_flags; 
std::vector<const _flag*> _normal_flags; 
std::vector<const _flag*> _low_flags; 
std::vector<const _flag*> _lowest_flags; 
for(auto& i : compare){ 
const _flag* itr = &i; 
if(!itr->tag.compare(compare[count].tag)){ 
switch(itr->weight){ 
case _p_r_i_o_r_i_t_y__l_e_v_e_l::_h_i_g_h_e_s_t: 
_highest_flags.push_back(itr); 
break; 
case _p_r_i_o_r_i_t_y__l_e_v_e_l::_h_i_g_h: 
_high_flags.push_back(itr); 
break; 
case _p_r_i_o_r_i_t_y__l_e_v_e_l::_n_o_r_m_a_l: 
_normal_flags.push_back(itr); 
break; 
case _p_r_i_o_r_i_t_y__l_e_v_e_l::_l_o_w: 
_low_flags.push_back(itr); 
break; 
case _p_r_i_o_r_i_t_y__l_e_v_e_l::_l_o_w_e_s_t: 
_lowest_flags.push_back(itr); 
break; 
} 
} 
count++; 
} 
_move_flags_into_queue(_highest_flags, _flag_queue); 
_move_flags_into_queue(_high_flags, _flag_queue); 
_move_flags_into_queue(_normal_flags, _flag_queue); 
_move_flags_into_queue(_low_flags, _flag_queue); 
_move_flags_into_queue(_lowest_flags, _flag_queue); 
} 
std::string _event::_flag_selector(const std::vector<_flag>& compare={}){ 
if(!_flag_queue.empty()){ 
std::string _selected_flag = _flag_queue.front()->tag; 
_flag_queue.erase(_flag_queue.begin()); 
return _selected_flag; 
} 
if(_delete_initial_flag){ 
std::string _initial_flag = _flag_list[0].tag; 
if(!_initial_flag.compare("_i_n_i_t_i_a_l _f_l_a_g")){ 
_flag_list.erase(_flag_list.begin()); 
_delete_initial_flag = false; 
return _initial_flag;} 
} 
if(!compare.empty()){ 
_flag_queue.clear(); 
_sort_and_populate_queue(compare); 
return _flag_selector(); 
} 
else{ 
std::string _initial_flag = _flag_list[0].tag; 
if(!_initial_flag.compare("_i_n_i_t_i_a_l _f_l_a_g")){ 
std::string _selected_flag = _flag_list[0].tag; 
return _selected_flag; 
} 
std::string _selected_flag = _flag_list[1].tag; 
return _selected_flag; 
} 
} 
void _event::_extract_story_from_file(){ 
std::string iffy = "/"+std::to_string(x_coordinate)+"/"+std::to_string(y_coordinate)+"/"+_flag_selector(); 
nlohmann::json::json_pointer poinr(iffy); 
_event_text = _story.at(poinr); 
} 
void _event::_display_event(){ 
_extract_story_from_file(); 
std::cout << _event_text << "\n"; 
} 
void _event::_set_flags(std::string &flag){_flag_list.push_back(_flag(flag));} 
void _event::_set_flag_weight(const std::string &flag, _p_r_i_o_r_i_t_y__l_e_v_e_l weight){ 
for(auto& i : _flag_list){ 
if(!i.tag.compare(flag)){ 
i.weight = weight; 
} 
_flag_queue.clear(); 
_sort_and_populate_queue(_flag_list); //might have to change this to make the generator 
} 
} 
