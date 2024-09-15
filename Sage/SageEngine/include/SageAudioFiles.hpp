typedef enum
{
    HALO_2,

    NUM_AUDIO_BGM
} Audio_BGM_Index;

static const char* Audio_BGM_Filepath(size_t _index)
{
    switch (_index)
    {
    case HALO_2:        return "../SageEngine/data/assets/audio/bgm/Halo 2 Soundtrack V2_ Epilogue.mp3";
    default:            return "";
    };
}

typedef enum
{
    BABABOOEY = NUM_AUDIO_BGM + 1,

    NUM_AUDIO_SFX
} Audio_SFX_Index;

static const char* Audio_SFX_Filepath(size_t _index)
{
    switch (_index)
    {
    case BABABOOEY:     return "../SageEngine/data/assets/audio/sfx/bababooey.mp3";
    default:            return "";
    };
}

typedef enum
{
    CLICK = NUM_AUDIO_SFX + 1,

    NUM_AUDIO_UI
} Audio_UI_Index;

static const char* Audio_UI_Filepath(size_t _index)
{
    switch (_index)
    {
    case CLICK:         return "../SageEngine/data/assets/audio/ui/click.ogg";
    default:            return "";
    };
}

typedef enum
{
    RAIN = NUM_AUDIO_UI + 1,

    NUM_AUDIO_AMBIENT
} Audio_Ambient_Index;

static const char* Audio_Ambient_Filepath(size_t _index)
{
    switch (_index)
    {
    case RAIN:          return "../SageEngine/data/assets/audio/ambient/rain.ogg";
    default:            return "";
    };
}

static size_t const g_maxAudio = NUM_AUDIO_AMBIENT;


static const char* Filepath_Getter(size_t _index)
{
    if (_index < NUM_AUDIO_BGM)
    {
        return Audio_BGM_Filepath(_index);
    }
    else if (_index < NUM_AUDIO_SFX)
    {
        return Audio_SFX_Filepath(_index);
    }
    else if (_index < NUM_AUDIO_UI)
    {
        return Audio_UI_Filepath(_index);
    }
    else
    {
        return Audio_Ambient_Filepath(_index);
    }
}