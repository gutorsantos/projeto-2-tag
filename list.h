#ifndef LIST_H_
#define LIST_H_

    #include "constants.h"
    #include <string.h>

    typedef struct Professor{
        int id;
        int qualification;
        int preferences[NUM_MAX_PREFERENCE];
        int is_hired;
    } Professor;

    typedef struct Vacancy {
        int qualification;
        int filled_by;
    }Vacancy;

    typedef struct School{
        int id;
        struct Vacancy vacancies[NUM_MAX_VACANCY];
    } School;

    Vacancy create_vacancy(int q) {
        Vacancy v;
        v.qualification = q;
        v.filled_by = 0;
        return v;
    }

    int is_vacancy_filled(Vacancy v) {
        return v.filled_by != 0 ? 1 : 0;
    }

    int is_preferences_empty(Professor p) {
        for(int i = 0; i < NUM_MAX_PREFERENCE; i++) {
            if(p.preferences[i])
                return 0;
        }
        return 1;
    }

    Professor create_professor(int id, int qualification, int preferences[]) {
        Professor p;
        p.id = id;
        p.qualification = qualification;
        p.is_hired = 0;
        memcpy(p.preferences, preferences, NUM_MAX_PREFERENCE*sizeof(int));
        return p;
    }

    Professor insert_professor(int id, int qualification, int preferences[]) {
        return create_professor(id, qualification, preferences);
    }

    int get_vancancy_num(Vacancy v[]) {
        return !v[1].qualification ? 1 : 2;
    }

    School create_school(int id, int requirements[]) {
        School s;
        int length = !requirements[1] ? 1 : 2;
        s.id = id;
        for(int i = 0; i < length; i++) {
            if(requirements[i])
                s.vacancies[i] = create_vacancy(requirements[i]);
            else
                s.vacancies[i] = create_vacancy(0);
        }
        return s;
    }

    School insert_school(int id, int requirements[]) {
        return create_school(id, requirements);
    }

    void print_matching(School school_list[], Professor prof_list[]) {
        for(int i = 1; i < NUM_SCHOOLS; i++) {
            printf("\nA escola %d possui os professores:\n\t%d", school_list[i].id, school_list[i].vacancies[0].filled_by);
            if(get_vancancy_num(school_list[i].vacancies) == 2) {
                printf("\n\t%d", school_list[i].vacancies[1].filled_by);
            }
        }
        /*
        printf("\n\nProfessores não alocados: \n");
        for(int i = 1; i < NUM_PROFS; i++) {
            if(!prof_list[i].is_hired)
                printf("%d %d [%d, %d, %d, %d]\n", prof_list[i].id, prof_list[i].qualification, prof_list[i].preferences[0], prof_list[i].preferences[1], prof_list[i].preferences[2], prof_list[i].preferences[3]);
        }*/

    }

#endif