//
// Created by Haoxiangpeng on 12/20/2016.
// Created and tested as per C99 standard
//
//Copyright (c) <year> <copyright holders>

//Permission is hereby granted, free of charge,
// to any person obtaining a copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct OneItem {
    long long plate_number;
    int time;
    int status;// in:1 out:0
    int valid;
    int stay_time;
};

long long str_to_long(char *str) {
    long long num = 1;// convert the string to long long type
    int i = 0;// so that we can easily sort the data
    while (str[i]) {
        num *= 100;
        num += str[i];
        i++;
    }// to avoid conflict
    return num;
}

char *long_to_string(long long num) {
    char *plate_number;// convert the long long type back to the string
    plate_number = malloc(sizeof(char) * 7);
    for (int i = 6; i >= 0; i--) {
        int temp = num % 100;
        plate_number[i] = (char) temp;
        num /= 100;// to avoid the conflict
    }
    plate_number[7] = '\0';// to mark the stop of the plate_number
    return plate_number;
}

int comp_by_in_time(const void *a, const void *b) {
    const struct OneItem *aa = (struct OneItem *) a;
    const struct OneItem *bb = (struct OneItem *) b;//cast the void* to target type
    return aa->time - bb->time;// compare by their in time
}

int comp_by_stay_time(const void *a, const void *b) {
    const struct OneItem *aa = (struct OneItem *) a;
    const struct OneItem *bb = (struct OneItem *) b;
    if (bb->stay_time != aa->stay_time)//cast the void* to target type
        return bb->stay_time - aa->stay_time;//compare by their in time
    else// if they have the same in time
        return bb->plate_number < aa->plate_number;//sort by their plate_number
}

int comp_by_stay_plate(const void *a, const void *b) {
    const struct OneItem *aa = (struct OneItem *) a;
    const struct OneItem *bb = (struct OneItem *) b;//cast the void* to target type
    return bb->plate_number > aa->plate_number;// sort by their plate_number
}


int main() {
    unsigned int RECORD, QURERY;
    struct OneItem *all_items;
    int *all_queries;
    scanf("%d%d", &RECORD, &QURERY);
    all_items = (struct OneItem *) malloc(sizeof(struct OneItem) * RECORD);//all the records
    all_queries = (int *) malloc(sizeof(int) * QURERY);// all the queries
    for (int i = 0; i < RECORD; i++) {
        char plate_number[10], tem_status[5];
        int hour, minute, second;
        scanf("%s %d:%d:%d %s", plate_number, &hour, &minute, &second, tem_status);//read from stdin
        all_items[i].plate_number = str_to_long(plate_number);
        all_items[i].time = hour * 3600 + minute * 60 + second;
        all_items[i].status = strcmp(tem_status, "in") ? -1 : 1;//if in then 1 else -1
        all_items[i].valid = -1;//initialize the data
        all_items[i].stay_time = 0;//initialize the data
    }
    for (int i = 0; i < QURERY; i++) {
        int hour, minute, second;
        scanf("%d:%d:%d", &hour, &minute, &second);
        all_queries[i] = hour * 3600 + minute * 60 + second;// convert the time to int, so that we can sort it
    }
    qsort(all_items, RECORD, sizeof(struct OneItem), comp_by_in_time);// Sort all the records per in time

    // eliminate the invalid items
    struct OneItem result_items[10000];//since we do not now how many valid item
    int result_number = 0;//mark the valid number
    for (int i = 0; i < RECORD; i++) {
        if (all_items[i].valid == 0) {
            continue;//already marked
        } else if (all_items[i].valid == 1) {
            result_items[result_number].stay_time = all_items[i].stay_time;
            result_items[result_number].plate_number = all_items[i].plate_number;
            result_items[result_number].status = all_items[i].status;
            result_items[result_number].time = all_items[i].time;
            result_number += 1;//copy the value to the target
            continue;
        }
        if (all_items[i].status == -1) {
            all_items[i].valid = 0;//if out first invalid then
            continue;
        }        //valid=-1 and status = 1
        int valid_flag = 0;
        for (int j = i + 1; j < RECORD; j++) {
            if (all_items[i].valid != -1)
                continue;
            if (all_items[i].plate_number == all_items[j].plate_number &&
                all_items[i].status == 1 && all_items[j].status == -1) {
                all_items[i].valid = 1;// if they have the same plate number
                all_items[j].valid = 1;// and they have different status, they got paired
                all_items[i].stay_time = all_items[j].time - all_items[i].time;
                all_items[j].stay_time = 0;// set the stay time, in to the correct out to zero

                result_items[result_number].stay_time = all_items[i].stay_time;
                result_items[result_number].plate_number = all_items[i].plate_number;
                result_items[result_number].status = all_items[i].status;//copy the source information
                result_items[result_number].time = all_items[i].time;//to the target one
                result_number += 1;//increment the counter
                valid_flag = 1;
                break;
            } else if (all_items[i].plate_number == all_items[j].plate_number &&
                       all_items[i].status == 1 && all_items[j].status == 1) {
                all_items[i].valid = 0;//if we encountered a same status
                valid_flag = 1;// it should be marked as illegal
                break;
            }
        }
        if (valid_flag == 0) {
            all_items[i].valid = 0;//not found and mark illegal
        }
    }

    // Print the query result
    int car_number = 0, query_index = 0, result_index = 0;
    while (query_index < QURERY) {
        if (result_items[result_index].time <= all_queries[query_index]) {//earlier than queried,status can only be 1 or -1
            car_number += (result_index < result_number ? result_items[result_index].status : 0);//if reached the end, status shall not change
            result_index++;// go to next car item
        } else {
            printf("%d\n", car_number);//out put the status number
            query_index++;//next query
        }
    }

    // Sort by plate number first, so that we can merge the time with O(N)
    qsort(result_items, (size_t) result_number, sizeof(struct OneItem), comp_by_stay_plate);
    for (int i = 0; i < result_number - 1; i++) {//merge the same car's plate time
        if (result_items[i].plate_number == result_items[i + 1].plate_number) {
            result_items[i + 1].stay_time += result_items[i].stay_time;
            result_items[i].stay_time = 0;//set one of the source to zero
        }
    }

    // Sort, the first key is stay time, second key is plate number
    qsort(result_items, (size_t) result_number, sizeof(struct OneItem), comp_by_stay_time);

    int index_number = 0;
    while (1) {//output the plate number
        printf("%s ", long_to_string(result_items[index_number].plate_number));//judge if we have two same entry
        if (result_items[index_number].stay_time != result_items[index_number + 1].stay_time) break;
        index_number++;//go to next
    }
    printf("%02d:%02d:%02d", result_items[0].stay_time / 3600, (result_items[0].stay_time % 3600) / 60,
           result_items[0].stay_time % 3600 % 60);//out put the top time
}
