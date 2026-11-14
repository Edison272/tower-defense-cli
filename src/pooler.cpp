//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "pooler.h"

#include <algorithm>

Pooler::Pooler(size_t minimumPoolSize) : minimumPoolSize(minimumPoolSize) {
    // prewarm pool based on min pool size
    for (size_t i = 0; i < minimumPoolSize; i++)
    {
        Enemy* new_enemy = CreateEnemy();

    }
}

size_t Pooler::PoolSize()
{
    return enemy_pool.size();
}

// clear the enemy pool
void Pooler::Clear(){}

// spawns an enemy. Takes in x/y coordinates via a  
// uses CreateEnemy() to spawn an enemy at a given position
Enemy* Pooler::SpawnEnemy(std::list<int> position) {
    return CreateEnemy();
}


// removes a given enemy from the game, and adds them to the pool
void Pooler::DespawnEnemy(Enemy* enemy) {}

// returns the enemies list
std::vector<Enemy*> Pooler::GetActiveEnemies() {
    return active_enemies;
}


// Creates an enemy, adds it to the pool
Enemy* Pooler::CreateEnemy() {
    return new Enemy();
}
