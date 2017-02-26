// This is a specific solution to Trending Today

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct Video
{
    int id;
    int size;
};

Video videos[10005];
int videoCount, endpointCount, requestCount, cacheCount, cacheCapacity;

int compareSizes(const void *v1, const void *v2)
{
    Video *p1 = (Video *)v1;
    Video *p2 = (Video *)v2;
    if(p1->size > p2->size)
    {
        return -1;
    }
    else if(p2->size > p1->size)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    scanf("%d %d %d %d %d", &videoCount, &endpointCount, &requestCount, &cacheCount,
          &cacheCapacity);

    for(int i = 0; i < videoCount; ++i)
    {
        Video *video = videos+i;
        video->id = i;
        scanf("%d", &video->size);
    }

    printf("%d\n", cacheCount);
    qsort(videos, videoCount, sizeof(Video), compareSizes);

    for(int i = 0; i < cacheCount; ++i)
    {
        int sum = cacheCapacity;
        printf("%d ", i);
        for(int j = 0; j < videoCount; ++j)
        {
            Video *video = videos+j;
            if(video->size <= sum)
            {
                printf("%d ", video->id);
                sum -= video->size;
                videos[j] = videos[--videoCount];
                --j;
            }
        }
        puts("");
    }

    return 0;
}
