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

#include "io/EntityModelLoader.h"
#include "mdl/Palette.h"

#include <filesystem>
#include <string>

namespace tb::io
{
class FileSystem;
class Reader;

class BspLoader : public EntityModelLoader
{
private:
  std::string m_name;
  const Reader& m_reader;
  const mdl::Palette m_palette;
  const FileSystem& m_fs;

public:
  BspLoader(
    std::string name, const Reader& reader, mdl::Palette palette, const FileSystem& fs);

  static bool canParse(const std::filesystem::path& path, Reader reader);

  Result<mdl::EntityModelData> load(Logger& logger) override;
};

} // namespace tb::io
