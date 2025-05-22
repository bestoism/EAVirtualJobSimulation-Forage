#ifndef DYNAMIC_CROWD_MOMENTUM_SYSTEM_H
#define DYNAMIC_CROWD_MOMENTUM_SYSTEM_H

#include <string>

// enum crowdState
enum class CrowdState {
    NORMAL,
    HYPED,
    TENSE,
    DEFLATED
};

// class gameEvent
class GameEvent {
private:
    std::string event_type;
    int impact_value;

public:
    GameEvent(); // constructor

    std::string getEventType() const;
    int getImpactValue() const;
    void setEventType(const std::string& type);
    void setImpactValue(int value);
};

// class momentumTracker
class MomentumTracker {
private:
    int current_momentum;

public:
    MomentumTracker(); // constructor

    void update_momentum(const GameEvent& game_event);
    CrowdState get_momentum_state() const;
};

// class crowdanimator
class CrowdAnimator {
public:
    CrowdAnimator(); // constructor

    void animate(CrowdState state);
};

// class audiomanager
class AudioManager {
public:
    AudioManager(); // constructor

    void adjust_audio(CrowdState state);
};

// class uieffectsmanager
class UIEffectsManager {
public:
    UIEffectsManager(); // constructor

    void trigger_effects(CrowdState state);
};

// class commentarymanager
class CommentaryManager {
public:
    CommentaryManager(); // constructor

    void commentate(CrowdState state);
};

// class accessibilitysettings
class AccessibilitySettings {
private:
    bool visual_effects_enabled;
    bool audio_effects_enabled;

public:
    AccessibilitySettings(); // constructor

    bool is_visual_effects_enabled() const;
    bool is_audio_effects_enabled() const;
    void set_visual_effects_enabled(bool enabled);
    void set_audio_effects_enabled(bool enabled);
};

// class crowdmanager
class CrowdManager {
private:
    MomentumTracker* momentum_tracker;
    CrowdAnimator* animator;
    AudioManager* audio_manager;
    UIEffectsManager* ui_manager;
    CommentaryManager* commentary_manager;
    AccessibilitySettings* accessibility;

public:
    CrowdManager(); // constructor

    void process_event(const GameEvent& game_event);
};

#endif 
