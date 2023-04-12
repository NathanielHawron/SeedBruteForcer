#pragma once
#include <vector>

#include "rand.h"
#include "chunk_coords.h"


namespace slimeChunkChecker{
    bool isSlimeChunk(long seed, int xPosition, int zPosition){
        return Random::randomInt(
            seed +
            (int) (xPosition * xPosition * 0x4c1906) +
            (int) (xPosition * 0x5ac0db) +
            (int) (zPosition * zPosition) * 0x4307a7L +
            (int) (zPosition * 0x5f24f) ^ 0x3ad8025f,

            10
        ) == 0;
    }
    void filterSeeds(int64_t min, int64_t max, std::vector<ChunkCoords> slimeChunks, std::vector<uint64_t> &res){
        for(int64_t i=min;i<max;++i){
            bool keep = true;
            for(int j=0;j<slimeChunks.size();++j){
                if(!isSlimeChunk(i,slimeChunks.at(j).x,slimeChunks.at(j).y)){
                    keep = false;
                    break;
                }
            }
            if(keep){
                res.push_back(i);
            }
        }
    }
    void filterSeeds(int64_t min, int64_t max, std::vector<ChunkCoords> slimeChunks, std::ofstream &res){
        for(int64_t i=min;i<max;++i){
            bool keep = true;
            for(int j=0;j<slimeChunks.size();++j){
                if(!isSlimeChunk(i,slimeChunks.at(j).x,slimeChunks.at(j).y)){
                    keep = false;
                    break;
                }
            }
            if(keep){
                res << i << '\n';
                res.flush();
            }
        }
    }
    void filterSeeds(std::vector<uint64_t> seeds, std::vector<ChunkCoords> slimeChunks, std::vector<uint64_t> &res){
        for(int64_t i=0;i<seeds.size();++i){
            bool keep = true;
            for(int j=0;j<slimeChunks.size();++j){
                if(!isSlimeChunk(seeds.at(i),slimeChunks.at(j).x,slimeChunks.at(j).y)){
                    keep = false;
                    break;
                }
            }
            if(keep){
                res.push_back(seeds.at(i));
            }
        }
    }
    void filterSeeds(std::vector<uint64_t> seeds, std::vector<ChunkCoords> slimeChunks, std::ofstream &res){
        for(int64_t i=0;i<seeds.size();++i){
            bool keep = true;
            for(int j=0;j<slimeChunks.size();++j){
                if(!isSlimeChunk(seeds.at(i),slimeChunks.at(j).x,slimeChunks.at(j).y)){
                    keep = false;
                    break;
                }
            }
            if(keep){
                res << seeds.at(i) << '\n';
            }
        }
    }
};