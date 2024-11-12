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

#include "DrawShapeTool.h"

#include "mdl/Brush.h" // IWYU pragma: keep
#include "mdl/BrushNode.h"
#include "ui/DrawShapeToolExtension.h"
#include "ui/DrawShapeToolExtensions.h"
#include "ui/DrawShapeToolPage.h"
#include "ui/MapDocument.h"

#include "kdl/memory_utils.h"
#include "kdl/range_to_vector.h"
#include "kdl/result.h"

#include <ranges>

namespace tb::ui
{

DrawShapeTool::DrawShapeTool(std::weak_ptr<MapDocument> document)
  : CreateBrushesToolBase{true, std::move(document)}
  , m_extensionManager{createDrawShapeToolExtensions()}
{
}

void DrawShapeTool::update(const vm::bbox3d& bounds)
{
  auto document = kdl::mem_lock(m_document);
  m_extensionManager.currentExtension().createBrushes(bounds, *document)
    | kdl::transform([&](auto brushes) {
        updateBrushes(
          brushes | std::views::transform([](auto brush) {
            return std::make_unique<mdl::BrushNode>(std::move(brush));
          })
          | kdl::to_vector);
      })
    | kdl::transform_error([&](auto e) {
        clearBrushes();
        document->error() << "Could not update brushes: " << e;
      });
}

bool DrawShapeTool::cancel()
{
  auto document = kdl::mem_lock(m_document);
  if (document->hasSelection())
  {
    // Let the map view deselect before we switch the shapes
    return false;
  }

  return m_extensionManager.setCurrentExtensionIndex(0);
}

QWidget* DrawShapeTool::doCreatePage(QWidget* parent)
{
  return new DrawShapeToolPage{m_document, m_extensionManager, parent};
}

} // namespace tb::ui
