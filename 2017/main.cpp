#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct Video
{
    int id;
    int size;
};

struct CacheConn
{
    int id;
    int lc;
};

struct Endpoint
{
    int ld;
    int k; // Num cache
    CacheConn conns[1005];
};

struct Request
{
    int videoId;
    int endpointId;
    int numRequests;
};

struct PossibleVid
{
    int id;
    long score;
};

struct Cache
{
    int id;
    int numPossible;
    PossibleVid possible[10005];
};

Video videos[10005];
Endpoint endpoints[1005];
Request requests[1000005];
Cache caches[1005];

int videoCount, endpointCount, requestCount, cacheCount, cacheCapacity;

int compareScores(const void *v1, const void *v2)
{
    PossibleVid *p1 = (PossibleVid *)v1;
    PossibleVid *p2 = (PossibleVid *)v2;
    if(p1->score > p2->score)
    {
        return -1;
    }
    else if(p2->score > p1->score)
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

    for(int i = 0; i < endpointCount; ++i)
    {
        Endpoint *endpoint = endpoints+i;
        scanf("%d %d", &endpoint->ld, &endpoint->k);

        for(int j = 0; j < endpoint->k; ++j)
        {
            CacheConn *conn = endpoint->conns + j;
            scanf("%d %d", &conn->id, &conn->lc);
        }
    }

    for(int i = 0; i < requestCount; ++i)
    {
        Request *request = requests+i;
        scanf("%d %d %d", &request->videoId, &request->endpointId, &request->numRequests);

        Endpoint *endpoint = endpoints + request->endpointId;
        for(int connIndex = 0; connIndex < endpoint->k; ++connIndex)
        {
            Cache *cache = caches + endpoint->conns[connIndex].id;
            int lat = endpoint->conns[connIndex].lc;
            int saved = endpoint->ld - lat;

            PossibleVid *possible = 0;
            for(int j = 0; j < cache->numPossible; ++j)
            {
                if(cache->possible[j].id == request->videoId)
                {
                    possible = cache->possible + j;
                    break;
                }
            }
            if(!possible)
            {
                possible = cache->possible + cache->numPossible++;
                possible->id = request->videoId;
            }

            possible->score += request->numRequests * saved;
        }
    }

    printf("%d\n", cacheCount);

    for(int i = 0; i < cacheCount; ++i)
    {
        printf("%d ", i);
        Cache *cache = caches+i;
        qsort(&cache->possible, cache->numPossible, sizeof(PossibleVid), compareScores);

        int sizeLeft = cacheCapacity;
        for(int j = 0; j < cache->numPossible && sizeLeft; ++j)
        {
            Video *video = videos + cache->possible[j].id;
            if(video->size <= sizeLeft)
            {
                sizeLeft -= video->size;
                printf("%d ", video->id);
            }
        }
        puts("");
    }

    return 0;
}
