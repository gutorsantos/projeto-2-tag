#ifndef MATCHING_H_
#define MATCHING_H_

    #include "graph.h"
    #include "list.h"
    #include "constants.h"

    int preferes_new(int new_prof, int old, int qualification) {
        if(new_prof == old)
            return 0;
        else {
            if(new_prof == qualification)
                return 1;
            if(new_prof >= qualification && new_prof <= old) {
                return 1;
            }
            
        }
        return 0;
    }

    int free_professor(Professor prof_list[]) {
        for(int i = 1; i < NUM_PROFS; i++) {
            //printf("ID: %d %d %d\n", prof_list[i].id, prof_list[i].is_hired, is_preferences_empty(prof_list[i]));
            if(!prof_list[i].is_hired && !is_preferences_empty(prof_list[i]))
                return i;
        }
        return 0;
    }

    int best_school(Professor p) {
        for(int i = 0; i < NUM_MAX_PREFERENCE; i++) {
            if(p.preferences[i] != 0)
                return i;
        }
        return 0;

    }

    int is_better_for_2nd(int q, Vacancy v[]) {
        if(v[0].qualification == v[1].qualification)
            return 0;
        else {
            if(q == v[1].qualification)
                return 1;
            if(q > v[1].qualification) {
                if(v[0].qualification > v[1].qualification) {
                    return 0;
                }
                return 1;
            }
        }
        return 0;
    }

    void gale_shapley(Graph* graph, Professor prof_list[], School school_list[]) {
        int id;
        
        // Finds the first id of free professor
        while(id = free_professor(prof_list)) {
            //Professor prof_list[id] = prof_list[id];
            if(!id)
                break;

            //printf("\n\nPROFESSOR %d\n", id);
            int preference_index = best_school(prof_list[id]);
            School* school = &school_list[prof_list[id].preferences[preference_index]];
            for(int i = 0; i < get_vancancy_num(school->vacancies); i++) {
                //printf("preferencia: %d = E%d vaga %d\n", preference_index, school->id, i+1);
                //printf("{%d %d}\n", school->vacancies[0].filled_by, school->vacancies[1].filled_by);
                if(!is_vacancy_filled(school->vacancies[i]) && school->vacancies[i].qualification <= prof_list[id].qualification) {
                    if(i == 0 && get_vancancy_num(school->vacancies) == 2)
                        if(is_better_for_2nd(prof_list[id].qualification, school->vacancies))
                            continue;
                    prof_list[id].is_hired = 1;
                    school->vacancies[i].filled_by = prof_list[id].id;
                    //printf("O professor %d foi alocado na escola %d\n", prof_list[id].id, school->id);
                    break;
                }
                if(is_vacancy_filled(school->vacancies[i])) {
                    if(preferes_new(prof_list[id].qualification, prof_list[school->vacancies[i].filled_by].qualification, school->vacancies[i].qualification)) {
                        if(i == 0 && get_vancancy_num(school->vacancies) == 2)
                            if(is_better_for_2nd(prof_list[id].qualification, school->vacancies))
                                continue;
                        //printf("A escola %d trocou o professor %d pelo %d\n", school->id, prof_list[school->vacancies[i].filled_by].id, prof_list[id].id);
                        prof_list[id].is_hired = 1;
                        //printf("novo professor esta contratado %d\n", prof_list[id].is_hired);
                        school->vacancies[i].filled_by = prof_list[id].id;
                        prof_list[school->vacancies[i].filled_by].is_hired = 0;
                        break;
                    }
                    
                }
            }
                prof_list[id].preferences[preference_index] = 0;
                //printf("[%d %d %d %d]", prof_list[id].preferences[0], prof_list[id].preferences[1], prof_list[id].preferences[2], prof_list[id].preferences[3]);
        }

    }

#endif