#include <iostream>
#include <filesystem>
#include <vector>
#include <cmath>
#include <fstream>
#include <thread>

#include "cli.h"

#include "rand.h"
#include "chunk_coords.h"
#include "slimeChunkGenerator.h"

#define PATH_APPEND_COPY(pathSrc, toAppend) std::filesystem::path(pathSrc).append(toAppend)

int main(int argc, char** argv){
    //Parse CLI arguments
    std::unordered_map<std::string, std::pair<cli::ARG_TYPE, std::any>> args;

    args["threads"] = std::pair(cli::ARG_TYPE::INT8, (int8_t)4);
    cli::parseArgs(argc, argv, args);
    std::cout << "Threadcount (Not yet implemented): " << (int)std::any_cast<int8_t>(args.at("threads").second) << std::endl;

    //Location of known features
    const std::filesystem::path coordsPath = std::filesystem::current_path().append("saves/coords");
    //Results folder
    const std::filesystem::path resultsPath = std::filesystem::current_path().append("saves/res");

    //Load in known features
    std::vector<ChunkCoords> slimeChunks;
    ChunkCoords::getCoordsFromFile(PATH_APPEND_COPY(coordsPath,"slimeChunks.txt"),slimeChunks);
    
    //Filter seeds
    std::ofstream file(PATH_APPEND_COPY(resultsPath,"res.txt"));
    slimeChunkChecker::filterSeeds(0,(uint64_t)std::pow(10,10),slimeChunks,file);
    file.close();
}