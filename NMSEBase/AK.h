#pragma once
enum AKRESULT
{
	AK_NotImplemented = 0,    ///< This feature is not implemented.
	AK_Success = 1,    ///< The operation was successful.
	AK_Fail = 2,    ///< The operation failed.
	AK_PartialSuccess = 3,    ///< The operation succeeded partially.
	AK_NotCompatible = 4,    ///< Incompatible formats
	AK_AlreadyConnected = 5,    ///< The stream is already connected to another node.
	AK_NameNotSet = 6,    ///< Trying to open a file when its name was not set
	AK_InvalidFile = 7,    ///< An unexpected value causes the file to be invalid.
	AK_AudioFileHeaderTooLarge = 8,    ///< The file header is too large.
	AK_MaxReached = 9,    ///< The maximum was reached.
	AK_InputsInUsed = 10,   ///< Inputs are currently used.
	AK_OutputsInUsed = 11,   ///< Outputs are currently used.
	AK_InvalidName = 12,   ///< The name is invalid.
	AK_NameAlreadyInUse = 13,   ///< The name is already in use.
	AK_InvalidID = 14,   ///< The ID is invalid.
	AK_IDNotFound = 15,   ///< The ID was not found.
	AK_InvalidInstanceID = 16,   ///< The InstanceID is invalid.
	AK_NoMoreData = 17,   ///< No more data is available from the source.
	AK_NoSourceAvailable = 18,   ///< There is no child (source) associated with the node.
	AK_StateGroupAlreadyExists = 19,   ///< The StateGroup already exists.
	AK_InvalidStateGroup = 20,   ///< The StateGroup is not a valid channel.
	AK_ChildAlreadyHasAParent = 21,   ///< The child already has a parent.
	AK_InvalidLanguage = 22,   ///< The language is invalid (applies to the Low-Level I/O).
	AK_CannotAddItseflAsAChild = 23,   ///< It is not possible to add itself as its own child.
	//AK_TransitionNotFound     = 24,   ///< The transition is not in the list.
	//AK_TransitionNotStartable = 25,   ///< Start allowed in the Running and Done states.
	//AK_TransitionNotRemovable = 26,   ///< Must not be in the Computing state.
	//AK_UsersListFull          = 27,   ///< No one can be added any more, could be AK_MaxReached.
	//AK_UserAlreadyInList      = 28,   ///< This user is already there.
	AK_UserNotInList = 29,   ///< This user is not there.
	AK_NoTransitionPoint = 30,   ///< Not in use.
	AK_InvalidParameter = 31,   ///< Something is not within bounds.
	AK_ParameterAdjusted = 32,   ///< Something was not within bounds and was relocated to the nearest OK value.
	AK_IsA3DSound = 33,   ///< The sound has 3D parameters.
	AK_NotA3DSound = 34,   ///< The sound does not have 3D parameters.
	AK_ElementAlreadyInList = 35,   ///< The item could not be added because it was already in the list.
	AK_PathNotFound = 36,   ///< This path is not known.
	AK_PathNoVertices = 37,   ///< Stuff in vertices before trying to start it
	AK_PathNotRunning = 38,   ///< Only a running path can be paused.
	AK_PathNotPaused = 39,   ///< Only a paused path can be resumed.
	AK_PathNodeAlreadyInList = 40,   ///< This path is already there.
	AK_PathNodeNotInList = 41,   ///< This path is not there.
	AK_VoiceNotFound = 42,   ///< Unknown in our voices list
	AK_DataNeeded = 43,   ///< The consumer needs more.
	AK_NoDataNeeded = 44,   ///< The consumer does not need more.
	AK_DataReady = 45,   ///< The provider has available data.
	AK_NoDataReady = 46,   ///< The provider does not have available data.
	AK_NoMoreSlotAvailable = 47,   ///< Not enough space to load bank.
	AK_SlotNotFound = 48,   ///< Bank error.
	AK_ProcessingOnly = 49,   ///< No need to fetch new data.
	AK_MemoryLeak = 50,   ///< Debug mode only.
	AK_CorruptedBlockList = 51,   ///< The memory manager's block list has been corrupted.
	AK_InsufficientMemory = 52,   ///< Memory error.
	AK_Cancelled = 53,   ///< The requested action was cancelled (not an error).
	AK_UnknownBankID = 54,   ///< Trying to load a bank using an ID which is not defined.
	AK_IsProcessing = 55,   ///< Asynchronous pipeline component is processing.
	AK_BankReadError = 56,   ///< Error while reading a bank.
	AK_InvalidSwitchType = 57,   ///< Invalid switch type (used with the switch container)
	AK_VoiceDone = 58,   ///< Internal use only.
	AK_UnknownEnvironment = 59,   ///< This environment is not defined.
	AK_EnvironmentInUse = 60,   ///< This environment is used by an object.
	AK_UnknownObject = 61,   ///< This object is not defined.
	AK_NoConversionNeeded = 62,   ///< Audio data already in target format, no conversion to perform.
	AK_FormatNotReady = 63,   ///< Source format not known yet.
	AK_WrongBankVersion = 64,   ///< The bank version is not compatible with the current bank reader.
	AK_DataReadyNoProcess = 65,   ///< The provider has some data but does not process it (virtual voices).
	AK_FileNotFound = 66,   ///< File not found.
	AK_DeviceNotReady = 67,   ///< IO device not ready (may be because the tray is open)
	AK_CouldNotCreateSecBuffer = 68,   ///< The direct sound secondary buffer creation failed.
	AK_BankAlreadyLoaded = 69,   ///< The bank load failed because the bank is already loaded.
	AK_RenderedFX = 71,   ///< The effect on the node is rendered.
	AK_ProcessNeeded = 72,   ///< A routine needs to be executed on some CPU.
	AK_ProcessDone = 73,   ///< The executed routine has finished its execution.
	AK_MemManagerNotInitialized = 74,   ///< The memory manager should have been initialized at this point.
	AK_StreamMgrNotInitialized = 75,   ///< The stream manager should have been initialized at this point.
	AK_SSEInstructionsNotSupported = 76,///< The machine does not support SSE instructions (required on PC).
	AK_Busy = 77,   ///< The system is busy and could not process the request.
	AK_UnsupportedChannelConfig = 78,   ///< Channel configuration is not supported in the current execution context.
	AK_PluginMediaNotAvailable = 79,   ///< Plugin media is not available for effect.
	AK_MustBeVirtualized = 80,   ///< Sound was Not Allowed to play.
	AK_CommandTooLarge = 81,   ///< SDK command is too large to fit in the command queue.
	AK_RejectedByFilter = 82,   ///< A play request was rejected due to the MIDI filter parameters.
	AK_InvalidCustomPlatformName = 83,   ///< Detecting incompatibility between Custom platform of banks and custom platform of connected application
	AK_DLLCannotLoad = 84,   ///< Plugin DLL could not be loaded, either because it is not found or one dependency is missing.
	AK_DLLPathNotFound = 85,   ///< Plugin DLL search path could not be found.
	AK_NoJavaVM = 86,   ///< No Java VM provided in AkInitSettings.
	AK_OpenSLError = 87,   ///< OpenSL returned an error.  Check error log for more details.
	AK_PluginNotRegistered = 88,   ///< Plugin is not registered.  Make sure to implement a AK::PluginRegistration class for it and use AK_STATIC_LINK_PLUGIN in the game binary.
	AK_DataAlignmentError = 89,   ///< A pointer to audio data was not aligned to the platform's required alignment (check AkTypes.h in the platform-specific folder)
};

