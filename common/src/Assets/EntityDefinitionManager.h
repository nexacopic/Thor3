/*
 Copyright (C) 2010-2014 Kristian Duske
 
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

#ifndef __TrenchBroom__EntityDefinitionManager__
#define __TrenchBroom__EntityDefinitionManager__

#include "Assets/AssetTypes.h"
#include "Assets/EntityDefinition.h"
#include "Assets/EntityDefinitionGroup.h"
#include "Model/ModelTypes.h"

#include <map>

namespace TrenchBroom {
    namespace IO {
        class EntityDefinitionLoader;
        class Path;
    }
    
    namespace Assets {
        class EntityDefinitionManager {
        private:
            typedef std::map<String, EntityDefinition*> Cache;
            EntityDefinitionList m_definitions;
            EntityDefinitionGroup::List m_groups;
            Cache m_cache;
        public:
            ~EntityDefinitionManager();

            void loadDefinitions(const IO::Path& path, const IO::EntityDefinitionLoader& loader);
            void clear();
            
            EntityDefinition* definition(const Model::Attributable* attributable) const;
            EntityDefinition* definition(const Model::AttributeValue& classname) const;
            EntityDefinitionList definitions(EntityDefinition::Type type, const EntityDefinition::SortOrder order = EntityDefinition::Name) const;

            const EntityDefinitionGroup::List& groups() const;
        private:
            void updateIndices();
            void updateGroups();
            void updateCache();
            void clearCache();
            void clearGroups();
        };
    }
}

#endif /* defined(__TrenchBroom__EntityDefinitionManager__) */
