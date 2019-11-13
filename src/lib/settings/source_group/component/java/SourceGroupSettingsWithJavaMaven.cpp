#include "SourceGroupSettingsWithJavaMaven.h"

#if BUILD_JAVA_LANGUAGE_PACKAGE

#include "ConfigManager.h"
#include "ProjectSettings.h"
#include "utilityFile.h"

FilePath SourceGroupSettingsWithJavaMaven::getMavenDependenciesDirectoryPath() const
{
	return getSourceGroupDependenciesDirectoryPath().concatenate(L"maven");
}

FilePath SourceGroupSettingsWithJavaMaven::getMavenProjectFilePath() const
{
	return m_mavenProjectFilePath;
}

FilePath SourceGroupSettingsWithJavaMaven::getMavenProjectFilePathExpandedAndAbsolute() const
{
	return utility::getExpandedAndAbsolutePath(getMavenProjectFilePath(), getProjectSettings()->getProjectDirectoryPath());
}

void SourceGroupSettingsWithJavaMaven::setMavenProjectFilePath(const FilePath& path)
{
	m_mavenProjectFilePath = path;
}

bool SourceGroupSettingsWithJavaMaven::getShouldIndexMavenTests() const
{
	return m_shouldIndexMavenTests;
}

void SourceGroupSettingsWithJavaMaven::setShouldIndexMavenTests(bool value)
{
	m_shouldIndexMavenTests = value;
}

bool SourceGroupSettingsWithJavaMaven::equals(const SourceGroupSettingsBase* other) const
{
	const SourceGroupSettingsWithJavaMaven* otherPtr = dynamic_cast<const SourceGroupSettingsWithJavaMaven*>(other);

	return (
		otherPtr &&
		m_mavenProjectFilePath == otherPtr->m_mavenProjectFilePath &&
		m_shouldIndexMavenTests == otherPtr->m_shouldIndexMavenTests
	);
}

void SourceGroupSettingsWithJavaMaven::load(const ConfigManager* config, const std::string& key)
{
	setMavenProjectFilePath(config->getValueOrDefault(key + "/maven/project_file_path", FilePath(L"")));
	setShouldIndexMavenTests(config->getValueOrDefault(key + "/maven/should_index_tests", false));
}

void SourceGroupSettingsWithJavaMaven::save(ConfigManager* config, const std::string& key)
{
	config->setValue(key + "/maven/project_file_path", getMavenProjectFilePath().wstr());
	config->setValue(key + "/maven/should_index_tests", getShouldIndexMavenTests());
}

#endif // BUILD_JAVA_LANGUAGE_PACKAGE