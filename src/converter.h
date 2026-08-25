#include <QJsonObject>
#include <optional>

#include "task.h"

QJsonObject task_to_json(const Task& task);

std::optional<Task> task_from_json(const QJsonObject& object);
