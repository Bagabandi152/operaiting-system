#include<stdio.h>
int main()
{
    int no_of_frames, no_of_pages, frames[10], temp[10], flag1, flag2, flag3, i, j, k, pos, max, faults = 0;
    no_of_frames = 3;
    no_of_pages = 20;

    int pages[20] = {7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1};

    for(i = 0; i < no_of_frames; ++i){
        frames[i] = -1;
    }

    for(i = 0; i < no_of_pages; ++i){
        flag1 = flag2 = 0;

        for(j = 0; j < no_of_frames; ++j){
            if(frames[j] == pages[i]){
                   flag1 = flag2 = 1;
                   break;
               }
        }

        if(flag1 == 0){
            for(j = 0; j < no_of_frames; ++j){
                if(frames[j] == -1){
                    faults++;
                    frames[j] = pages[i];
                    flag2 = 1;
                    break;
                }
            }
        }

        if(flag2 == 0){
            flag3 =0;

            for(j = 0; j < no_of_frames; ++j){
            temp[j] = -1;

            for(k = i + 1; k < no_of_pages; ++k){
                 if(frames[j] == pages[k]){
                     temp[j] = k;
                     break;
                     }
                 }
            }

            for(j = 0; j < no_of_frames; ++j){
                 if(temp[j] == -1){
                     pos = j;
                     flag3 = 1;
                     break;
                 }
            }

            if(flag3 ==0){
                max = temp[0];
                pos = 0;

                 for(j = 1; j < no_of_frames; ++j){
                     if(temp[j] > max){
                     max = temp[j];
                     pos = j;
                     }
                 }
            }
            frames[pos] = pages[i];
            faults++;
        }

        printf("\n");

        for(j = 0; j < no_of_frames; ++j){
            printf("%d\t", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d", faults);

    return 0;
}
