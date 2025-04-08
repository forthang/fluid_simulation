# Симуляция жидкости с использованием метода SPH

Данный проект реализует симуляцию жидкости методом сглаженных частиц (SPH) для курсовой работы по компьютерной графике или вычислительной физике.

## Основные особенности
- Реализация базового алгоритма SPH на C++
- Оптимизации для повышения производительности
- Визуализация с использованием OpenGL
- Поддержка взаимодействия жидкости с твердыми телами
- Настраиваемые параметры симуляции

## Зависимости
- C++17 или новее
- OpenGL 3.3+
- GLFW
- Glad
- glm
- (опционально) CUDA для GPU-ускорения

## Сборка и запуск
```bash
mkdir build && cd build
cmake ..
make
./fluid_simulation
