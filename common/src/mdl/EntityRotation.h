/*
 Copyright (C) 2010 Kristian Duske

 This file is part of TrenchBroom.

 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


#include "kdl/reflection_decl.h"

#include "vm/mat.h"
#include "vm/vec.h"

#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

namespace tb::mdl
{
class Entity;
class EntityProperty;
enum class PitchType;
struct EntityPropertyConfig;

enum class EntityRotationType
{
  None,
  Angle,
  AngleUpDown,
  Euler,
  Euler_PositivePitchDown,
  Mangle
};

std::ostream& operator<<(std::ostream& lhs, const EntityRotationType& rhs);

enum class EntityRotationUsage
{
  Allowed,
  BlockRotation
};

std::ostream& operator<<(std::ostream& lhs, const EntityRotationUsage& rhs);

struct EntityRotationInfo
{
  const EntityRotationType type;
  const std::string propertyKey;
  const EntityRotationUsage usage;

  kdl_reflect_decl(EntityRotationInfo, type, propertyKey, usage);
};

EntityRotationInfo entityRotationInfo(const Entity& entity);

vm::mat4x4d entityRotation(
  const std::vector<EntityProperty>& properties, const EntityRotationInfo& info);

vm::mat4x4d entityRotation(const Entity& entity);

vm::vec3d entityYawPitchRoll(
  const vm::mat4x4d& transformation, const vm::mat4x4d& rotation);

std::optional<EntityProperty> applyEntityRotation(
  const std::vector<EntityProperty>& properties,
  const EntityRotationInfo& info,
  const vm::mat4x4d& transformation);
void applyEntityRotation(Entity& entity, const vm::mat4x4d& transformation);

} // namespace tb::mdl
