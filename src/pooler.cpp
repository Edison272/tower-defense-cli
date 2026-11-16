//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "pooler.h"

#include <algorithm>

Pooler::Pooler(size_t minimumPoolSize) : minimumPoolSize(minimumPoolSize) {
    // prewarm pool based on min pool size
    for (size_t i = 0; i < minimumPoolSize; i++) {
        Enemy* new_enemy = new Enemy();
        enemy_storage.push_back(*new_enemy);
        enemy_pool.push_back(new_enemy);
    }
}
Pooler::~Pooler() {
    ClearPointers();
}

size_t Pooler::PoolSize() const
{
    return enemy_pool.size();
}

// clear the enemy pool
void Pooler::Clear(){
    ClearPointers();
    
    while(enemy_storage.size() > minimumPoolSize)
    {
        enemy_storage.pop_back();
    }
    for (Enemy enemy : enemy_storage) {
        enemy_pool.push_back(&enemy);
    }
}

// deletes pointers to memory
void Pooler::ClearPointers()
{
    for (Enemy* enemy : active_enemies)
        delete enemy;
    for (Enemy* enemy : enemy_pool)
        delete enemy;
}

// spawns an enemy. Takes in x/y coordinates via a  
// uses CreateEnemy() to spawn an enemy at a given position
Enemy* Pooler::SpawnEnemy(Vector2D position) {
    Enemy* new_enemy = CreateEnemy();
    new_enemy->Activate(position);
}


// removes a given enemy from the game, and adds them to the pool
void Pooler::DespawnEnemy(Enemy* enemy) {
    if (enemy == nullptr)
        return;

    auto it = std::find(active_enemies.begin(), active_enemies.end(), enemy);
    if (it == active_enemies.end())
        return; // not active; avoids double-pooling

    enemy->Deactivate();

    *it = active_enemies.back();
    active_enemies.pop_back();

    enemy_pool.push_back(enemy);
}

const std::vector<Enemy*>& Pooler::GetActiveEnemies() const {
    return active_enemies;
}

// Creates an enemy, adds it to the pool
Enemy* Pooler::CreateEnemy() {
    Enemy* new_enemy = nullptr;

    // draw from pool if possible
    if (!enemy_pool.empty()) {
        new_enemy = enemy_pool.back();
        enemy_pool.pop_back();
    } else {
        new_enemy = new Enemy();
        enemy_storage.push_back(*new_enemy);
    }

    active_enemies.push_back(new_enemy);
    return new_enemy;
}
