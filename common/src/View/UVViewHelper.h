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

#include "Model/BrushFaceHandle.h"
#include "Model/HitType.h"

#include "vm/bbox.h"
#include "vm/mat.h"
#include "vm/ray.h"
#include "vm/vec.h"

#include <optional>

namespace TrenchBroom::Assets
{
class Material;
}

namespace TrenchBroom::Renderer
{
class ActiveShader;
class Camera;
class OrthographicCamera;
class RenderContext;
} // namespace TrenchBroom::Renderer

namespace TrenchBroom::Model
{
class BrushFace;
class PickResult;
} // namespace TrenchBroom::Model

namespace TrenchBroom::View
{

class UVViewHelper
{
private:
  Renderer::OrthographicCamera& m_camera;
  bool m_zoomValid = false;

  std::optional<Model::BrushFaceHandle> m_faceHandle;

  vm::vec2i m_subDivisions = {1, 1};

  /**
   The position of the scaling origin / rotation center handle in world coords.
   */
  vm::vec3d m_origin;

public:
  explicit UVViewHelper(Renderer::OrthographicCamera& camera);

  bool valid() const;
  const Model::BrushFace* face() const;
  const Assets::Material* material() const;
  void setFaceHandle(std::optional<Model::BrushFaceHandle> faceHandle);
  void cameraViewportChanged();

  const vm::vec2i& subDivisions() const;
  vm::vec2d stripeSize() const;
  void setSubDivisions(const vm::vec2i& subDivisions);

  const vm::vec3d origin() const;
  const vm::vec2f originInFaceCoords() const;
  const vm::vec2f originInUVCoords() const;
  void setOriginInFaceCoords(const vm::vec2f& originInFaceCoords);

  const Renderer::OrthographicCamera& camera() const;
  float cameraZoom() const;

  void pickUVGrid(
    const vm::ray3d& ray,
    const Model::HitType::Type hitTypes[2],
    Model::PickResult& pickResult) const;

  vm::vec2f snapDelta(const vm::vec2f& delta, const vm::vec2f& distance) const;
  vm::vec2f computeDistanceFromUVGrid(const vm::vec3d& position) const;

  void computeOriginHandleVertices(
    vm::vec3d& x1, vm::vec3d& x2, vm::vec3d& y1, vm::vec3d& y2) const;
  void computeScaleHandleVertices(
    const vm::vec2d& pos,
    vm::vec3d& x1,
    vm::vec3d& x2,
    vm::vec3d& y1,
    vm::vec3d& y2) const;
  void computeLineVertices(
    const vm::vec2d& pos,
    vm::vec3d& x1,
    vm::vec3d& x2,
    vm::vec3d& y1,
    vm::vec3d& y2,
    const vm::mat4x4d& toTex,
    const vm::mat4x4d& toWorld) const;

  /**
   * Converts UV space to view space (pixels in the UV viewport).
   */
  vm::vec2f uvToViewCoords(const vm::vec2f& pos) const;

private:
  void resetOrigin();
  void resetCamera();
  void resetZoom();

  vm::bbox3d computeFaceBoundsInCameraCoords() const;
  vm::vec3d transformToCamera(const vm::vec3d& point) const;
  vm::vec3d transformFromCamera(const vm::vec3d& point) const;
};

} // namespace TrenchBroom::View
