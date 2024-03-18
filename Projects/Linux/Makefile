# GNU Makefile to create the executable and contents of
# CSPong for linux

PROJECT_NAME=CSTest
SOURCES += /Accelerometer/AccelerometerPresenter.cpp
SOURCES += /Accelerometer/State.cpp
SOURCES += /AnimatedModel/State.cpp
SOURCES += /App.cpp
SOURCES += /Common/Behaviour/FollowerComponent.cpp
SOURCES += /Common/Behaviour/OrbiterComponent.cpp
SOURCES += /Common/Core/Approx.cpp
SOURCES += /Common/Core/BasicEntityFactory.cpp
SOURCES += /Common/Core/ResultPresenter.cpp
SOURCES += /Common/Core/TestNavigator.cpp
SOURCES += /Common/Input/BackButtonSystem.cpp
SOURCES += /Common/UI/BasicWidgetFactory.cpp
SOURCES += /Common/UI/OptionsMenuDesc.cpp
SOURCES += /Common/UI/OptionsMenuPresenter.cpp
SOURCES += /CricketAudio/State.cpp
SOURCES += /Cubemap/State.cpp
SOURCES += /CustomShader/State.cpp
SOURCES += /Device/DevicePresenter.cpp
SOURCES += /Device/State.cpp
SOURCES += /DialogueBox/State.cpp
SOURCES += /DownloadProgress/DownloadProgressTestSystem.cpp 
SOURCES += /DownloadProgress/State.cpp
SOURCES += /EmailComposer/State.cpp
SOURCES += /Gamepad/GamepadPresenter.cpp
SOURCES += /Gamepad/State.cpp
SOURCES += /Gesture/EventInfo.cpp
SOURCES += /Gesture/GesturePresenter.cpp
SOURCES += /Gesture/State.cpp
SOURCES += /IntegrationTest/State.cpp
SOURCES += /IntegrationTest/TestSystem/Report.cpp
SOURCES += /IntegrationTest/TestSystem/ReportPresenter.cpp
SOURCES += /IntegrationTest/TestSystem/Test.cpp
SOURCES += /IntegrationTest/TestSystem/TestDesc.cpp
SOURCES += /IntegrationTest/TestSystem/Tester.cpp
SOURCES += /IntegrationTest/TestSystem/TestRegistry.cpp
SOURCES += /IntegrationTest/Tests/BinaryInputStreamTest.cpp 
SOURCES += /IntegrationTest/Tests/BinaryOutputStreamTest.cpp
SOURCES += /IntegrationTest/Tests/FileSystemTest.cpp
SOURCES += /IntegrationTest/Tests/HttpRequestTest.cpp
SOURCES += /IntegrationTest/Tests/RenderCommandCompilerTest.cpp
SOURCES += /IntegrationTest/Tests/TaskSchedulerTest.cpp
SOURCES += /IntegrationTest/Tests/TextInputStreamTest.cpp
SOURCES += /IntegrationTest/Tests/TextOutputStreamTest.cpp
SOURCES += /Keyboard/KeyboardPresenter.cpp
SOURCES += /Keyboard/State.cpp
SOURCES += /Lighting/State.cpp
SOURCES += /LocalNotifications/State.cpp
SOURCES += /MainMenu/State.cpp
SOURCES += /Particle/State.cpp
SOURCES += /RemoteNotifications/RemoteNotificationsPresenter.cpp
SOURCES += /RemoteNotifications/State.cpp
SOURCES += /RenderToTexture/State.cpp
SOURCES += /Screen/ScreenPresenter.cpp
SOURCES += /Screen/State.cpp
SOURCES += /SmokeTest/State.cpp
SOURCES += /Sprite/State.cpp
SOURCES += /TextEntry/State.cpp
SOURCES += /TextEntry/TextEntryPresenter.cpp
SOURCES += /UI/State.cpp
SOURCES += /UnitTest/State.cpp
SOURCES += /UnitTest/TestSystem/CSReporter.cpp
SOURCES += /UnitTest/TestSystem/FailedAssertion.cpp
SOURCES += /UnitTest/TestSystem/FailedSection.cpp
SOURCES += /UnitTest/TestSystem/FailedTestCase.cpp
SOURCES += /UnitTest/TestSystem/Report.cpp
SOURCES += /UnitTest/TestSystem/ReportPresenter.cpp
SOURCES += /UnitTest/TestSystem/TestSystem.cpp
SOURCES += /UnitTest/Tests/LinearAllocator.cpp
SOURCES += /UnitTest/Tests/ObjectPoolAllocator.cpp
SOURCES += /UnitTest/Tests/PagedLinearAllocator.cpp
SOURCES += /UnitTest/Tests/ShapeIntersection.cpp
SOURCES += /UnitTest/Tests/Vector2.cpp
SOURCES += /UnitTest/Tests/Vector3.cpp
SOURCES += /UnitTest/Tests/Vector4.cpp
SOURCES += /VideoPlayer/State.cpp
SOURCES += /WebView/State.cpp

OBJECTS = $(call source_to_object, $(SOURCES))
DEPENDENCIES = $(call object_to_depend, $(OBJECTS))

SOLUTION_DIR = .

MKDIR = mkdir -p

PLATFORM = Linux
SRC_DIR = ../../AppSource/
CATCH_LIB_HEADERS = ../../Libraries/Catch/include
CHILLISOURCE_DIR = ../../ChilliSource
CHILLISOURCE_SCRIPTS_DIR = $(CHILLISOURCE_DIR)/Tools/Scripts
CHILLISOURCE_PROJECT_DIR = $(CHILLISOURCE_DIR)/Projects/$(PLATFORM)
CHILLISOURCE_HEADERS_DIR = $(CHILLISOURCE_DIR)/Source/
CORE_LIB_DIR = $(CHILLISOURCE_DIR)/Libraries/Core/$(PLATFORM)
CRICKET_LIB_DIR = $(CHILLISOURCE_DIR)/Libraries/CricketAudio/$(PLATFORM)
CHILLISOURCE_LIB_DIR = $(CHILLISOURCE_PROJECT_DIR)/csbin/$(PLATFORM)
OBJ_DIR = $(SOLUTION_DIR)/csobj/$(PLATFORM)/
OUT_DIR = $(SOLUTION_DIR)/csbin/$(PLATFORM)/
TARGET_ARCHITECTURE = x86_64
TARGET_VERSION = release

LIBS_LINUX = CSBase  sfml-window-s sfml-system-s curl ssl crypto GLEW z
SHARED_LIBS_LINUX = X11 Xrandr Xcursor GL udev asound ogg pthread

#CPPFLAGS += -fpermissive
# add compiler use c++11 flags
CPPFLAGS += -std=c++11 -std=gnu++11 
# add compiler debug flag for debug versions and debug defines
CPPFLAGS += $(if $(or $(call eq,$(TARGET_VERSION),debug),$(call eq,$(TARGET_VERSION),DEBUG)), -g -D_DEBUG -DDEBUG -DCS_ENABLE_DEBUG)
# add compiler flag for each architecture
CPPFLAGS += $(if $(call eq,$(TARGET_ARCHITECTURE),x86_64), -m64 )
CPPFLAGS += $(if $(call eq,$(TARGET_ARCHITECTURE),x86_32), -m32 )
# add needed include path
CPPFLAGS += -I $(SRC_DIR) -I $(CORE_LIB_DIR)/Headers -I $(CHILLISOURCE_HEADERS_DIR) 
CPPFLAGS += -I $(CATCH_LIB_HEADERS)
CPPFLAGS += -include string -include cstring
# add platform define
CPPFLAGS += -DCS_TARGETPLATFORM_$(call to_upper,$(PLATFORM))
# add libChilliSource library flags 
CPPFLAGS += -Wl,-Bstatic
CPPFLAGS += -L$(CHILLISOURCE_LIB_DIR)/$(TARGET_ARCHITECTURE)/$(TARGET_VERSION) 
CPPFLAGS += -lChilliSource
# add dependency defines and library flags 
# NOTE:Always using release version of libraries even in debug build
CPPFLAGS += -DGLEW_STATIC -DSFML_STATIC
CPPFLAGS += -L$(CRICKET_LIB_DIR)/Libs/$(TARGET_ARCHITECTURE)/release 
CPPFLAGS += -lck
CPPFLAGS += -L$(CORE_LIB_DIR)/Libs/$(TARGET_ARCHITECTURE)/release 
CPPFLAGS += $(foreach lib,$(LIBS_$(call to_upper,$(PLATFORM))), -l$(lib))
# add shared libraries flag (assumed part of the system)
CPPFLAGS += -Wl,-Bdynamic
CPPFLAGS += $(foreach lib,$(SHARED_LIBS_$(call to_upper,$(PLATFORM))), -l$(lib))


# Helper Macros
eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))
contains = $(findstring $(1),$(2))
to_upper = $(shell echo $(1) | tr '[a-z]' '[A-Z]')
# $(call source_to_object, source_file_list) 
source_to_object = $(subst .c,.o,$(filter %.c,$1)) \
                   $(subst .cpp,.o,$(filter %.cpp,$1))
# $(call source_to_depend, source_file_list) 
source_to_depend = $(subst .c,.d,$(filter %.c,$1)) \
                   $(subst .cpp,.d,$(filter %.cpp,$1))
# $(call object_to_depend, object_file_list) 
object_to_depend = $(subst .o,.d,$(filter %.o,$1)) 
# $(call make-depend,source-file,object-file,depend-file)
define make-depend
 $(COMPILE.cpp) -MM -MF $3 -MP -MT $2 $1
endef

OUT_PREFIX_DIR = $(OUT_DIR)$(TARGET_ARCHITECTURE)/$(TARGET_VERSION)
OBJ_PREFIX_DIR = $(OBJ_DIR)$(PROJECT_NAME)/$(TARGET_ARCHITECTURE)/$(TARGET_VERSION)
# $(call make_object_rule,source-file,object-file,depend-file)
define make_object_rule

$2 : $1
	$$(MKDIR) $$(dir $(2))
	$$(call make-depend, $1, $2, $3)
	$$(COMPILE.cpp) $1 -o $$@
endef


#Target rules
all : $(OUT_PREFIX_DIR)/$(PROJECT_NAME) copy_resources

# include generated object dependencies
ifneq "$(MAKECMDGOALS)" "clean"
 $(foreach dependency,$(DEPENDENCIES),       \
    $(eval -include $(OBJ_PREFIX_DIR)/$(dependency))\
 ) 
endif


# rule to run ChiliSource project make 
.PHONY: $(CHILLISOURCE_PROJECT_DIR)
$(CHILLISOURCE_PROJECT_DIR):
	$(MAKE) --directory=$@ PLATFORM=$(PLATFORM) TARGET_ARCHITECTURE=$(TARGET_ARCHITECTURE) TARGET_VERSION=$(TARGET_VERSION) 

.PHONY: clean
clean :
	rm -r csobj || true

.PHONY: clean_all
clean_all: clean
	$(MAKE) --directory=$(CHILLISOURCE_PROJECT_DIR) clean

# make object target rules
$(foreach source, $(SOURCES), \
 $(eval $(call make_object_rule, \
  $(SRC_DIR)/$(source), \
  $(addprefix $(OBJ_PREFIX_DIR)/,$(call source_to_object, $(source))), \
  $(addprefix $(OBJ_PREFIX_DIR)/,$(call source_to_depend, $(source))) \
  ))\
)

OBJ_PREFIX_DIR_OBJECTS = $(addprefix $(OBJ_PREFIX_DIR)/,$(OBJECTS))
$(OUT_PREFIX_DIR)/$(PROJECT_NAME) : $(OBJ_PREFIX_DIR_OBJECTS) $(CHILLISOURCE_PROJECT_DIR)
	$(MKDIR) $(OUT_PREFIX_DIR)
	$(LINK.cpp) -o $(OUT_PREFIX_DIR)/$(PROJECT_NAME) $(OBJ_PREFIX_DIR_OBJECTS) $(CPPFLAGS)


.PHONY : copy_resources
copy_resources :
	python $(CHILLISOURCE_SCRIPTS_DIR)/copy_linux_resources.py "$(SOLUTION_DIR)/" "$(OUT_PREFIX_DIR)"

