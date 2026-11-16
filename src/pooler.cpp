//Copyright 2K Games, Engineering Graduate Program. All rights reserved. DO NOT redistribute.

#include "pooler.h"

#include <algorithm>

Pooler::Pooler(size_t minimumPoolSize) : minimumPoolSize(minimumPoolSize) {
    Reset();
}
size_t Pooler::PoolSize() const
{
    return enemy_pool.size();
}

// clear the enemy pool
void Pooler::Clear(){
    Reset();
}

// Resets pool back to base state. clears previous pool and reinitializes with new one 
void Pooler::Reset() {
    // clear pointers
    active_enemies.clear();
    enemy_pool.clear();

    // remove extra instances or fill in new ones
    while (enemy_storage.size() > minimumPoolSize)
        enemy_storage.pop_back();
    while (enemy_storage.size() < minimumPoolSize)
        enemy_storage.emplace_back();

    // add any newly created enemies to the pool
    for (Enemy& e : enemy_storage) {
        e.Deactivate();
        enemy_pool.push_back(&e);
    }
}

// spawns an enemy. Takes in x/y coordinates via a  
// uses CreateEnemy() to spawn an enemy at a given position
Enemy* Pooler::SpawnEnemy(Vector2D position) {
    Enemy* new_enemy = CreateEnemy();
    new_enemy->Activate(position);
    return new_enemy;
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

// Creates an enemy, adds it to active_enemy
Enemy* Pooler::CreateEnemy() {
    Enemy* new_enemy = nullptr;

    // draw from pool if possible
    if (!enemy_pool.empty()) {
        new_enemy = enemy_pool.back();
        enemy_pool.pop_back();
    } else {
        enemy_storage.emplace_back();
        new_enemy = &enemy_storage.back();
    }

    active_enemies.push_back(new_enemy);
    return new_enemy;
}
