/*
 Copyright (C) 2023 iOrange
 Copyright (C) 2023 Kristian Duske

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

#include "Assets/Material.h"
#include "Assets/Palette.h"
#include "IO/DiskFileSystem.h"
#include "IO/DiskIO.h"
#include "IO/File.h"
#include "IO/ReadDdsTexture.h"
#include "TestUtils.h"

#include "kdl/result.h"

#include <filesystem>
#include <memory>

#include "Catch2.h"

namespace TrenchBroom
{
namespace IO
{
static Assets::Material loadTexture(const std::string& name)
{
  const auto ddsPath = std::filesystem::current_path() / "fixture/test/IO/Dds/";
  auto diskFS = DiskFileSystem{ddsPath};

  const auto file = diskFS.openFile(name).value();
  auto reader = file->reader().buffer();
  return readDdsTexture(name, reader).value();
}

static void assertMaterial(
  const std::string& name, const size_t width, const size_t height, const GLenum format)
{
  const auto texture = loadTexture(name);

  CHECK(texture.name() == name);
  CHECK(texture.texture().width() == width);
  CHECK(texture.texture().height() == height);
  CHECK(texture.texture().format() == format);
  CHECK(texture.texture().mask() == Assets::TextureMask::Off);
}

TEST_CASE("ReadDdsTextureTest.testLoadDds")
{
  assertMaterial("dds_rgb.dds", 128, 128, GL_BGR);
  assertMaterial("dds_rgba.dds", 128, 128, GL_BGRA);
  assertMaterial("dds_bc1.dds", 128, 128, GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
  assertMaterial("dds_bc2.dds", 128, 128, GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
  assertMaterial("dds_bc3.dds", 128, 128, GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
}
} // namespace IO
} // namespace TrenchBroom
