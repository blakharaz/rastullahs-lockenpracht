/* This source file is part of Rastullahs Lockenpracht.
 * Copyright (C) 2003-2008 Team Pantheon. http://www.team-pantheon.de
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the Clarified Artistic License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  Clarified Artistic License for more details.
 *
 *  You should have received a copy of the Clarified Artistic License
 *  along with this program; if not you can get it here
 *  http://www.jpaulmorrison.com/fbp/artistic2.htm.
 */

//%template(GameObjectVector) std::vector< rl::GameObject* >;

namespace rl {

    // Before first use of GameObject or subclasses!
    %apply SWIGTYPE *DYNAMIC { rl::GameObject * };

                    
   template<typename T>
   class Tripel {
   public:
      T first;
      T second;
      T third;

      Tripel();      
      Tripel(const T& t1, const T& t2, const T& t3);
      Tripel(const Tripel& rhs);

      //Tripel& operator=(const Tripel& rhs);
      bool operator==(const Tripel& rhs);
      bool operator<(const Tripel& rhs);     
   };
    
    class Date {
    public:
        static const RL_LONGLONG ONE_SECOND = 1000ULL;
        static const RL_LONGLONG ONE_MINUTE = 60000ULL;
        static const RL_LONGLONG ONE_HOUR = 3600000ULL;
        static const RL_LONGLONG ONE_DAY = 86400000ULL;
        static const RL_LONGLONG ONE_WEEK = 604800000ULL;
        static const RL_LONGLONG ONE_MONTH = 2592000000ULL;
        static const RL_LONGLONG ONE_YEAR = 31536000000ULL;
        static const RL_LONGLONG ONE_KAMPFRUNDE = 2 * ONE_SECOND;
        static const RL_LONGLONG ONE_SPIELRUNDE = 5 * ONE_MINUTE;

        Date();
        Date(RL_LONGLONG timestamp);
        Date(const Date& rhs);
      
        bool operator==(const Date& rhs);
        bool operator<(const Date& rhs);
        bool operator<=(const Date& rhs);
        bool operator>=(const Date& rhs);
        bool operator>(const Date& rhs);

        Date operator+(const RL_LONGLONG& rhs);
        Date operator-(const RL_LONGLONG& rhs);
        Date operator*(const Ogre::Real& rhs);
        Date operator/(const Ogre::Real& rhs);
        RL_LONGLONG operator-(const Date& rhs);
      
        RL_LONGLONG getTimestamp();

        int getTimeFraction();
        int getYear();
        int getMonth();
        rl::CeGuiString getMonthName();
        int getDayOfYear();
        int getDayOfMonth();
        int getDayOfWeek();
        rl::CeGuiString getDayOfWeekName();
        int getHour();
        int getMinute();
        int getSecond();
        int getMilliSecond();
      
        rl::CeGuiString toString();
    };
   
    Date operator+(const RL_LONGLONG&, const Date&);
    Date operator-(const RL_LONGLONG&, const Date&);

    class RulesSubsystem 
    {
        public:
             static rl::RulesSubsystem& getSingleton();
             rl::QuestBook* getQuestBook();
             void resetQuestBook();
    };
  
    class DsaManager {
    public:
        RL_LONGLONG getTimestamp();
        Date getCurrentDate();
        void setCurrentDate(const Date& date);
        
        int rollD20();
        Tripel<int> roll3D20();
        int rollD6();
        int roll(int d6, int d20);
      
        static DsaManager& getSingleton();
        rl::Talent* getTalent(const rl::CeGuiString name) const;
        rl::Creature* getCreature(const int id) const;
    };
    
    %feature("director") GameObjectFactory; 
    class GameObjectFactory
    {
    public:
        virtual rl::GameObject* createRubyGameObject(const Ogre::String& classname, unsigned int id) = 0;
        GameObjectFactory();
        virtual ~GameObjectFactory();
    };
    
    class GameObjectManager
    {
    public:
        static rl::GameObjectManager& getSingleton();
        rl::GameObject* createGameObject(const Ogre::String& classId, unsigned int id = 0);
        rl::GameObject* getGameObject(unsigned int id) const;
        void setGameObjectFactory(rl::GameObjectFactory* gof);
        rl::GameObjectList getAllGameObjects();

    private:
        GameObjectManager();
    };

	enum GameEventType
	{
		GET_DEFAULT,
		GET_COMBAT,
		GET_DIALOG,
		GET_QUEST
	};
	
    class GameEventLog
    {
    public:
        static rl::GameEventLog& getSingleton();
		void logEvent(const Ogre::String& eventString, GameEventType type);

    private:
        GameEventLog();
    };
    
    class GlobalProperties 
    {
    public:
        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
        bool hasProperty(const Ogre::String& key) const;
        
        static rl::GlobalProperties& getSingleton();
    private:
        GlobalProperties();
    };

    %feature("director") QuestListener; 
    class QuestListener
    {
    public:
        virtual ~QuestListener();
        
        virtual void questStateChanged(rl::QuestEvent* anEvent) = 0;
        virtual void questPartsDoneChanged(rl::QuestEvent* anEvent) = 0;
        virtual void questKnownChanged(rl::QuestEvent* anEvent) = 0;
        virtual void questSubquestAdded(rl::QuestEvent* anEvent) = 0;
        virtual void journalEntryAdded(rl::JournalEvent* anEvent) = 0;
        virtual void journalEntryDeleted(rl::JournalEvent* anEvent) = 0;
    };

    class JournalEntry
    {
    public:
        JournalEntry(const rl::CeGuiString caption, const rl::CeGuiString text);
        virtual ~JournalEntry();

        rl::CeGuiString getCaption() const;

        rl::CeGuiString getText() const;
    };
    
    class Quest
    {
    public:
        enum State
        {
            OPEN = 0,
            ASSIGNED,
            FAILED,
            SUCCEEDED,
            COMPLETED
        };

        Quest(const rl::CeGuiString id, const rl::CeGuiString name, const rl::CeGuiString description);
        virtual ~Quest();

        const rl::CeGuiString getId();
        const rl::CeGuiString getName();
        const rl::CeGuiString getDescription();
        int getPartsToDo();
        void setPartsToDo(int partsToDo);
        int getPartsDone();
        void setPartsDone(int partsDone);
        void increasePartsDone(int parts = 1);
        void decreasePartsDone(int parts = 1);

        rl::Quest::State getState();
        void setState(rl::Quest::State state);
        bool isKnown();
        void setKnown(bool known);

        // QuestVector getSubquests();
        void addSubquest(rl::Quest* quest); 
    };   
    
    class QuestEvent
    {
    public:
        rl::Quest* getQuest();
    private:
        QuestEvent( rl::QuestBook* src, int reason );
    };
    
    class QuestBook
    {
    public:
        rl::Quest* getQuest(const rl::CeGuiString id);
        void addQuest(rl::Quest* quest);
        
        void addJournalEntry(rl::JournalEntry* entry);
        void addJournalEntry(rl::CeGuiString caption, rl::CeGuiString text);
        
        void addQuestListener(rl::QuestListener* listener);
        void removeQuestListener(rl::QuestListener* listener);
    };
    
    class Talent
    {
    public:
        typedef std::map<const rl::CeGuiString,int> AusweichTalente;
        Talent(const rl::CeGuiString name,
               const rl::CeGuiString description,
               const Tripel<rl::CeGuiString>& eigenschaften,
               int ebe,
               int gruppe,
               const rl::CeGuiString art,
               const AusweichTalente &ausweichTalente);

        bool operator==(const Talent& rhs) const;
        bool operator<(const Talent& rhs) const;
        rl::CeGuiString getName() const;
        rl::CeGuiString getDescription() const;
        int getEbe() const;

        /// Berechnet effektive Behinderung bei gegebener Behinderung;
        int calculateEbe(int be) const;
        Tripel<rl::CeGuiString> getEigenschaften() const;
    };

    class ActionGroup
    {
    public:
        ActionGroup(rl::CeGuiString name, ActionGroup* parent = NULL);
        ~ActionGroup();
    
        const rl::CeGuiString getName() const;
    };
    
    %feature("director") Action;   
    class Action
    {
    public:
        static const int ACT_NORMAL = 1<<0;
        static const int ACT_INVIS_DESC = 1<<1;
        static const int ACT_DISABLED = 1<<2;
        static const int ACT_NEEDS_TALENT = 1<<8;

        static const int TC_NO_TARGET = 0;
        static const int TC_GAMEOBJECT = 1;
        static const int TC_CREATURE = 2;
        static const int TC_ITEM = 3;
        static const int TC_POINT = 4;
        static const int TC_RADIUS = 5;
        static const int TC_POINT_AND_RADIUS = 6;
    
        Action(const rl::CeGuiString name, const rl::CeGuiString description);
        virtual ~Action();

        virtual const rl::CeGuiString getName() const;
        //virtual const rl::CeGuiString getClassName() const;
        virtual const rl::CeGuiString getDescription() const;
        virtual int getTargetClass() const;
        virtual void doAction(rl::GameObject *object, rl::Creature *actor,
            rl::GameObject *target);
        virtual bool canDo(rl::GameObject* object, rl::Creature* actor, rl::GameObject* target = NULL) const;
            
        void setGroup(rl::ActionGroup* group);
        rl::ActionGroup* getGroup() const;
    };
    
    %feature("director") ObjectStateChangeListener;      
    class ObjectStateChangeListener      
    {      
    public:      
        virtual ~ObjectStateChangeListener();      
               
        virtual void objectStateChanged(rl::ObjectStateChangeEvent *anEvent) = 0;      
    };
              
               
    class ObjectStateChangeEventSource      
    {      
    public:      
        ObjectStateChangeEventSource( );      
               
        void addObjectStateChangeListener( rl::ObjectStateChangeListener*  list );      
        void removeObjectStateChangeListener( rl::ObjectStateChangeListener* list );      
        bool hasListeners( ) const;      
        rl::GameObject* getObject() const;
        void fireObjectStateChangeEvent();      
    };      
               
    class ObjectStateChangeEvent      
    {      
    public:      
        ObjectStateChangeEvent( rl::ObjectStateChangeEventSource* src );      
        rl::GameObject* getProvokingObject() const;      
        rl::ObjectStateChangeEventSource* getSource() const;      
    };
            
    enum GameObjectState
    {
        GOS_UNDEFINED = 0,
        GOS_UNLOADED,
        GOS_LOADED,
        GOS_IN_POSSESSION,
        GOS_IN_SCENE,
        GOS_HELD,
        GOS_READY
    };
    
    class PropertyRecord
    {
    public:
        PropertyRecord();
        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
    };
    
    %constant unsigned long QUERYFLAG_GAMEOBJECT = rl::QUERYFLAG_GAMEOBJECT;
    %constant unsigned long QUERYFLAG_CREATURE = rl::QUERYFLAG_CREATURE;
    %constant unsigned long QUERYFLAG_ITEM = rl::QUERYFLAG_ITEM;
    %constant unsigned long QUERYFLAG_CONTAINER = rl::QUERYFLAG_CONTAINER;
    %constant unsigned long QUERYFLAG_WEAPON = rl::QUERYFLAG_WEAPON;
    %constant unsigned long QUERYFLAG_ARMOR = rl::QUERYFLAG_ARMOR;
    %constant unsigned long QUERYFLAG_PERSON = rl::QUERYFLAG_PERSON;
    %constant unsigned long QUERYFLAG_PLAYER = rl::QUERYFLAG_PLAYER;
    
    %feature("director") GameObject;
    class GameObject: public ObjectStateChangeEventSource
    {
    public:
        GameObject(unsigned int id);
        virtual ~GameObject();

        virtual unsigned int getId();

        virtual const rl::CeGuiString getName() const;
        virtual void setName(rl::CeGuiString name);

        const rl::CeGuiString getDescription() const;
        virtual void setDescription(rl::CeGuiString description);   
        
        void setActor(rl::Actor* actor);
        rl::Actor* getActor();

        void addAction(rl::Action *action, int option = ACT_NORMAL);
        void addActionInGroup(Action* action, ActionGroup* group, int option = ACT_NORMAL);
        void removeAction(rl::Action *action);

        const std::vector<Action*> getValidActions(rl::Creature *actor) const;        
        void setPosition(const Ogre::Vector3& position);
        void setOrientation(const Ogre::Quaternion& orientation);
        const Ogre::Quaternion& getOrientation() const;
        const Ogre::Vector3& getPosition() const;
        
        void setMeshfile(rl::CeGuiString meshfile);
        
        virtual Action* getDefaultAction(rl::Creature* actor) const;
        
        void doAction(
            const rl::CeGuiString actionName, 
            rl::Creature* actor,
            rl::GameObject* target);
        void doAction(
            const rl::CeGuiString actionName);
        void doAction(rl::Action* action, rl::Creature* actor,
            rl::GameObject* target);
            
        void doDefaultAction(rl::Creature* actor, rl::GameObject* target);
            
        static const rl::CeGuiString DEFAULT_VIEW_OBJECT_ACTION;
        static const rl::CeGuiString DEFAULT_VIEW_OBJECT_ACTION_DEBUG;
        
        bool isHighlightingEnabled();
        void setHighlightingEnabled( bool highlightenabled );
        
        void addEffect(rl::Effect* effect);
        void addEffectWithCheckTime(rl::Effect* effect, RL_LONGLONG time);
        void addEffectWithCheckDate(rl::Effect* effect, RL_LONGLONG date);
        void removeEffect(rl::Effect* effect);
        
        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
        
        virtual void placeIntoScene();
        void removeFromScene();
        
        rl::GameObjectState getState() const;
        void setState(rl::GameObjectState state);
        
        unsigned long getQueryFlags() const;
        void addQueryFlag(unsigned long queryflag);
        void setQueryFlags(unsigned long queryflags);
        
        virtual void onBeforeStateChange(GameObjectState oldState, GameObjectState newState);
        virtual void onAfterStateChange(GameObjectState oldState, GameObjectState newState);
    };
    
    class WaitJob : public rl::Job
    {
    public:
        WaitJob(const rl::Date& dsatime);
        WaitJob(const Ogre::Real& realtime);
    };
    
    class GoToJob : public rl::Job
    {
    public:

		GoToJob(rl::Creature* actor, const Ogre::Vector3& targetPos,
			Ogre::Real maxDistance, Ogre::Real duration,
            rl::CreatureController::MovementType movementType_moving = rl::CreatureController::MT_RENNEN,
            rl::CreatureController::MovementType movementType_idle = rl::CreatureController::MT_STEHEN);
		GoToJob(rl::Creature* actor, rl::GameObject* target, Ogre::Real maxDistance, Ogre::Real duration, bool followTarget = false,
            rl::CreatureController::MovementType movementType_moving = rl::CreatureController::MT_RENNEN,
            rl::CreatureController::MovementType movementType_idle = rl::CreatureController::MT_STEHEN);
    };
    
    /// A rl#Job to fetch an item
    class FetchItemJob : public Job
    {
    public:

		FetchItemJob(rl::Creature* actor, rl::Item* item, const Ogre::String& targetSlot, Ogre::Real duration);
    };
    
    %feature("director") Item;
    class Item : public rl::GameObject {
    public:
        enum ItemType{
            ITEMTYPE_WEAPON     = 1 << 0,
            ITEMTYPE_SHIELD     = 1 << 1,
            ITEMTYPE_RING       = 1 << 2,
            ITEMTYPE_GLOVES     = 1 << 3,
            ITEMTYPE_BRACELET   = 1 << 4,
            ITEMTYPE_ARMOR      = 1 << 5,
            ITEMTYPE_CAPE       = 1 << 6,
            ITEMTYPE_BRACERS    = 1 << 7,
            ITEMTYPE_BACKPACK   = 1 << 8,
            ITEMTYPE_BELT       = 1 << 9,
            ITEMTYPE_NECKLACE   = 1 << 10,
            ITEMTYPE_HELMET     = 1 << 11,
            ITEMTYPE_TROUSERS   = 1 << 12,
            ITEMTYPE_SHINBONE   = 1 << 13,
            ITEMTYPE_BOOTS      = 1 << 14,
            ITEMTYPE_CLOTHES    = 1 << 15,
            ITEMTYPE_OTHER      = 1 << 16,
            ITEMTYPE_ALL_ITEMS  = ~(0)
        };
    
        Item(unsigned int id);
        virtual ~Item();
        
        virtual void placeIntoScene();
        
        void setItemType(rl::Item::ItemType itemType);
        rl::Item::ItemType getItemType() const;
        virtual void setState(rl::GameObjectState state);
        virtual void removeOldState();

        void setParentSlot(rl::Slot* slot);
        rl::Slot* getParentSlot() const;

        void setParentContainer(rl::Container* cont);
        rl::Container* getParentContainer() const;

        void setOwner(rl::GameObject* go);
        rl::GameObject* getOwner() const;

        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
        virtual bool isContainer();
        
        virtual void onBeforeStateChange(GameObjectState oldState, GameObjectState newState);
        virtual void onAfterStateChange(GameObjectState oldState, GameObjectState newState);
    };
    
    %feature("director") Weapon;
    class Weapon : public rl::Item 
    {
    public:
        enum Distanzklasse { DK_H=0, DK_N, DK_S, DK_P };

        Weapon(unsigned int id);
        virtual ~Weapon();
                
        void setTp(int d6, int d20, int mod);
        const Tripel<int>& getTp() const;
        void setTpKk(int base, int step);
        const std::pair<int, int>& getTpKk() const;
        void setBf(int newBf);
        int getBf();
        void setIni(int newIni);
        int getIni();
        void setWm(std::pair<int, int>& newWm);
        const std::pair<int,int>& getWm() const;
        void setDk(Weapon::Distanzklasse newDk);
        Weapon::Distanzklasse getDk();
        void setKampftechnik(const rl::CeGuiString newKampftechnik);
        const rl::CeGuiString getKampftechnik() const;

        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
        
        virtual void onBeforeStateChange(GameObjectState oldState, GameObjectState newState);
        virtual void onAfterStateChange(GameObjectState oldState, GameObjectState newState);
    };
    
    %feature("director") Armor;
    class Armor : public Item
    {
    public:
    
        static const CeGuiString Armor::PROPERTY_G_BE = "g_be";
        static const CeGuiString Armor::PROPERTY_G_RS = "g_rs";
        
        Armor(unsigned int id);
        virtual ~Armor();

        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
        
        virtual void onBeforeStateChange(GameObjectState oldState, GameObjectState newState);
        virtual void onAfterStateChange(GameObjectState oldState, GameObjectState newState);
    };
    
    %feature("director") Container;
    class Container : public Item
    {
    public:
        Container(unsigned int id);
        virtual ~Container();

        Ogre::Real getCapacity() const;
        void setCapacity(Ogre::Real capacity);
        void setVolume(unsigned int x, unsigned int y);
        Ogre::Real getContentWeight() const;
        void addItem(rl::Item* item);
        void removeItem(rl::Item* item);
        rl::ItemSet getItems() const;
        int getItemCount() const;
        rl::Item* getItemAt(unsigned int x, unsigned int y);

        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
        
        virtual void onBeforeStateChange(GameObjectState oldState, GameObjectState newState);
        virtual void onAfterStateChange(GameObjectState oldState, GameObjectState newState);
    };
    

    %feature("director") Effect;
    class Effect
    {
    public:    
        typedef unsigned long LifeState;
        static const LifeState LS_NONE           = 1<<0;
        static const LifeState LS_BLIND          = 1<<1;   ///< The creature can't see anything.
        static const LifeState LS_DEAD           = 1<<2;   ///< The creature is dead.
        static const LifeState LS_DEAF           = 1<<3;   ///< The creature can't hear anything.
        static const LifeState LS_PARALYZED      = 1<<4;   ///< The creature can't move, turn, jump etc.
        static const LifeState LS_INCAPACITATED  = 1<<5;   ///< The creature can't fight anymore due to serious injuries. The creature can barely move.
        static const LifeState LS_INVISIBLE      = 1<<6;   ///< The creature can't be seen.
        static const LifeState LS_INVULNERABLE   = 1<<7;   ///< The creature is immune to any mundane attacks.
        static const LifeState LS_PETRIFIED      = 1<<8;   ///< The creature is coated with stone and has all the effects of paralyzation
        static const LifeState LS_SILENCED       = 1<<9;   ///< The creature doesn't make any noises.
        static const LifeState LS_SLEEPING       = 1<<10;  ///< The creature is asleep.
        static const LifeState LS_UNCONSCIOUS    = 1<<11;  ///< Like SLEEPING, but more difficult to wake.

        // Meta stati
        static const LifeState LS_IMMOBILE = LS_PARALYZED | LS_SLEEPING | LS_UNCONSCIOUS | LS_PETRIFIED | LS_DEAD;
        static const LifeState LS_NO_COMBAT = LS_IMMOBILE | LS_INCAPACITATED;

        typedef int ModType;
        static const ModType MODTYPE_NONE         = 1 << 0;
        static const ModType MODTYPE_SUM      = 1 << 1;   ///< Modifies the actual value.
        static const ModType MODTYPE_PROBENMOD    = 1 << 2;   ///< Modifies the test.
        static const ModType MODTYPE_MULT     = 1 << 3;   ///< Will be multiplied on the value.
        static const ModType MODTYPE_MAXWERTMOD   = 1 << 4;   ///< Modifies only the maximum of the value.

        typedef unsigned long ModTag;
        static const ModTag MODTAG_NONE           = 1 << 0;
        static const ModTag MODTAG_KRANKHEIT      = 1 << 1;
        static const ModTag MODTAG_RECALCULATE    = 1 << 2;
        static const ModTag MODTAG_REGENERATION_LE = 1 << 3;
        static const ModTag MODTAG_REGENERATION_AE = 1 << 4;
        static const ModTag MODTAG_REGENERATION_AU = 1 << 5;
        static const ModTag MODTAG_ERSCHOEPFUNGSSCHWELLE = 1 << 6;
    
        enum Quantifier
        {
            QUANTIFIER_MULTIPLE,
            QUANTIFIER_UNIQUE,
            QUANTIFIER_UNIQUE_BUT_PROLONGABLE,
            QUANTIFIER_UNIQUE_BUT_CUMULATIVE
        };
        
      // other constants
        static const int REMOVE = -1;
        static const int PERMANENT = 0;


        Effect(int stufe = 1);
        virtual ~Effect();

        const Ogre::String getName() const;
        void setName(Ogre::String name);
        const rl::CeGuiString getDescription() const;
        void setDescription(rl::CeGuiString description);
        Quantifier getQuantifier();
        void setQuantifier(Quantifier quantifier);
        virtual const int getStufe();
        virtual void increaseStufe();
        virtual void decreaseStufe();
        virtual void enable();
        virtual void disable();
        virtual RL_LONGLONG timeCheck() = 0;

        virtual LifeState getLifeState() const;
        virtual int getMod(rl::CeGuiString target, ModType type, ModTag tag);

        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);
        virtual rl::PropertyKeys getAllPropertyKeys() const;
    };

    class EffectFactory
    {
    public:
        virtual rl::Effect* createEffect(const Ogre::String& name, int stufe) = 0;
    };

    class EffectFactoryManager
    {
    public:
        void setEffectFactory(rl::EffectFactory* factory);
        static rl::EffectFactoryManager& getSingleton();
    };

    enum SlotType
    {
        SLOT_BONE,
        SLOT_SUBMESH,
        SLOT_MATERIAL
    };

    class Inventory 
    {
    private:
        Inventory(rl::Creature* owner);
    public:
        void addSlot(const rl::CeGuiString& name, const Ogre::String& meshpartname, int itemReadyMask, int itemHeldMask, SlotType type = SLOT_BONE);
        rl::Item* getItem(const rl::CeGuiString& slotName) const;
        void hold(rl::Item* item, const rl::CeGuiString& slot);
        void ready(rl::Item* item, const rl::CeGuiString& slot);
        void dropItem(const rl::CeGuiString& slotName);
    };

    %feature("director") Creature;
    class Creature : public GameObject {
    public:
    
    typedef Ogre::String Wert;
        enum Alignment
        {
            ALIGNMENT_ALLY,    ///< Creature fights with the player.
            ALIGNMENT_NEUTRAL, ///< Creature doesn't fight for either side.
            ALIGNMENT_ENEMY    ///< Creature fights against the player.
        };

        enum SfStatus
        {
            SFSTATUS_IN_TRAINING = 1,
            SFSTATUS_OK,
            SFSTATUS_REQUIREMENTS_NOT_MET /// @todo Wird das ueberhaupt gebraucht?
        };

        // some targets
        static const std::string Creature::ALL_EIGENSCHAFTEN = "alle Eigenschaften";
        static const std::string Creature::ALL_TALENTE = "alle Talente";
        static const Creature::Wert Creature::WERT_MOD_AE = "ModAE";
        static const Creature::Wert Creature::WERT_MOD_LE = "ModLE";
        static const Creature::Wert Creature::WERT_MOD_AU = "ModAU";
        static const Creature::Wert Creature::WERT_MOD_MR = "ModMR";
        static const Creature::Wert Creature::WERT_MOD_AT = "ModAT";
        static const Creature::Wert Creature::WERT_MOD_PA = "ModPA";
        static const Creature::Wert Creature::WERT_MOD_FK = "ModFK";
        static const Creature::Wert Creature::WERT_GS = "GS";
        static const Creature::Wert Creature::WERT_SOZIALSTATUS = "SO";
        static const Creature::Wert Creature::WERT_BE = "BE";
        static const Creature::Wert Creature::WERT_RS = "RS";
        static const Creature::Wert Creature::WERT_INI = "INI";
        static const Creature::Wert Creature::WERT_KAMPFUNFAEHIGKEITSSCHWELLE ="Kampfunfaehigkeitsschwelle"; 
        static const Creature::Wert Creature::WERT_REGENERATION = "Regeneration";
        
        
        Creature(unsigned int id);
        virtual ~Creature();

        virtual int getLe();
        virtual void modifyLe(int mod, bool ignoreMax = false);
        virtual void modifyAe(int mod);
        virtual void modifyAu(int mod);
        void setWert(Wert wertId, int value);
        virtual int getWert(Wert wertId, bool getUnmodified = false);
        
        virtual int getEigenschaft(const rl::CeGuiString eigenschaftName, Effect::ModTag tag = Effect::MODTAG_NONE);
        virtual void setEigenschaft(const rl::CeGuiString eigenschaftName, int value);
        virtual void modifyEigenschaft(const rl::CeGuiString eigenschaftName, int mod);

        
        void addTalent(const rl::CeGuiString talentName, int value=0);
        bool hasTalent(const rl::CeGuiString talentName, bool checkAusweichTalente = true);
        virtual int getTalent(const rl::CeGuiString talentName);
        virtual void setTalent(const rl::CeGuiString talentName, int value);
        virtual void modifyTalent(const rl::CeGuiString talentName, int mod);
        virtual void addSe(const rl::CeGuiString talentName);
        
        void addVorteil(const rl::CeGuiString vorteilName, int value = 0);
        void addNachteil(const rl::CeGuiString nachteilName, int value = 0);        
        
        void addKampftechnik(const rl::CeGuiString kampftechnikName, std::pair<int,int> value = make_pair(0,0));
        virtual void addSf(const rl::CeGuiString sfName, SfStatus value = SFSTATUS_IN_TRAINING);
        
        virtual int doTalentprobe(const rl::CeGuiString talentName, int modifier);
        virtual int doEigenschaftsprobe(const rl::CeGuiString eigenschaftName, int modifier);
        
        rl::Inventory* getInventory();
        
        void damageLe(int tp, int damageType = LEDAMAGE_NORMAL);
        static const int LEDAMAGE_NORMAL = 0;
        static const int LEDAMAGE_FIRE = 1;
        static const int LEDAMAGE_WATER = 2;
        static const int LEDAMAGE_DEMONIC = 4;
        void damageAu(int aup, int damageType = AUDAMAGE_NORMAL);
        static const int AUDAMAGE_NORMAL = 0;
        static const int AUDAMAGE_HEAT = 1;
        static const int AUDAMAGE_COLD = 2;
        static const int AUDAMAGE_CHOKE = 4;
        static const int AUDAMAGE_DROWN = 8;

        virtual const rl::Property getProperty(const rl::CeGuiString& key) const;
        virtual void setProperty(const rl::CeGuiString& key, const rl::Property& value);

        void setAlignment(Alignment);
        Alignment getAlignment() const;
        
        virtual void onBeforeStateChange(GameObjectState oldState, GameObjectState newState);
        virtual void onAfterStateChange(GameObjectState oldState, GameObjectState newState);
   };
   
    %feature("director") ActionManager;
    class ActionManager
    {
    public:
        void registerAction(rl::Action* action);
        void unregisterAction(const rl::CeGuiString actionName);
        rl::Action* getAction(const rl::CeGuiString actionName) const;

        void registerInGameGlobalAction(rl::Action* action, rl::ActionGroup* group);
    
        static rl::ActionManager& getSingleton();
    };
    
    class CreatureController
    {
    public:
        
        typedef enum
        {
            // these movements can be used
            MT_NONE,
            MT_STEHEN,
            MT_GEHEN,
            MT_JOGGEN,
            MT_LAUFEN,
            MT_RENNEN,
            MT_RUECKWAERTS_GEHEN,
            MT_RUECKWAERTS_JOGGEN,
            MT_SEITWAERTS_GEHEN,
            MT_SCHLEICHEN,
            MT_HOCHSPRUNG,
            MT_WEITSPRUNG,
            MT_ZIELSPRUNG,
            // these movements are only for internal purposes and should not be used directly
            // instead use one of the movements above
            MT_DREHEN,
            MT_STUFENERKENNUNG,
            MT_FALLEN,
            MT_LIEGEN
        } MovementType;
        
        Creature *getCreature();
        bool setMovement(MovementType type, Ogre::Vector3 direction, Ogre::Vector3 rotation);
        MovementType getMovementId() const;
        Ogre::Vector3 getDirection() const;
        Ogre::Vector3 getRotation() const;
        Ogre::Vector3 getVelocity() const;
        Ogre::Vector3 getOmega() const;
        void setAnimation(const Ogre::String &name, 
                          Ogre::Real speed = 1, 
                          unsigned int timesToPlay = 0, 
                          const Ogre::String &collisionName = "");
    protected:
        CreatureController(Creature *character);
        ~CreatureController();
    };
    
    class CreatureControllerManager
    {
    public:
        /// Returns a CreatureController that can be used to control given Creature.
        /// There is only one controller per Creature at a given time.
        /// If no such controller exists yet, it is created.
        rl::CreatureController* getCreatureController(rl::Creature* creature);

        /// This function detaches a controller attached to the given Creature, if any.
        void detachController(rl::Creature* creature);

        static rl::CreatureControllerManager& getSingleton();
    };

	// Before first use of Selector or subclasses!
    %apply SWIGTYPE *DYNAMIC { rl::Selector* };

	class Selector
    {
    public:
        Selector(unsigned long mask = 0xffffffff);
        virtual void updateSelection();

        void setSelectionMask(unsigned long mask);
        unsigned long getSelectionMask() const;

        GameObject* getFirstSelectedObject() const;
		const rl::GameObjectList& getAllSelectedObjects() const;
		unsigned int getSelectionCount() const;

		virtual void updatePrimitive() = 0;
    };


    /// A Selector that selects all unoccluded GameObject the ray hits.
    class RaySelector : public Selector
    {
    public:
        RaySelector(unsigned long mask = 0xffffffff, bool useOgreQuery = false);
        void setRay(const Ogre::Vector3& start, const Ogre::Vector3& end);
		virtual void updatePrimitive();
    };

    /// Selects this GameObject within a half sphere pointing to -Z,
    /// that has the smallest angle difference to the -Z-Axis.
    class HalfSphereSelector : public Selector
    {
    public:
        HalfSphereSelector(unsigned long mask = 0xffffffff);
	    void setRadius(Ogre::Real radius);
        void setPosition(const Ogre::Vector3& pos);
        void setOrientation(const Ogre::Quaternion& ori);
		virtual void updatePrimitive();
	};

    /// Selects GameObjects within a sphere.
    class SphereSelector : public Selector
    {
    public:
        SphereSelector(unsigned long mask = 0xffffffff);
	    void setRadius(Ogre::Real radius);
        void setPosition(const Ogre::Vector3& pos);
		virtual void updatePrimitive();
    };
    
    class PartyManager
    {
    public:
        void setActiveCharacter(Creature* character);
        Creature* getActiveCharacter() const;
        void addCharacter(Creature* character);
        void removeCharacter(Creature* character);
        static PartyManager& getSingleton();
    };

} // Namespace

%{
static swig_type_info *Selector_dynamic_cast(void **ptr)
{
	rl::Selector *pSelector = static_cast<rl::Selector*>(*ptr);
	rl::HalfSphereSelector *pHalfSphereSel = dynamic_cast<rl::HalfSphereSelector*>(pSelector);
	if (pHalfSphereSel)
	{
		*ptr = pHalfSphereSel;
		return SWIGTYPE_p_rl__HalfSphereSelector;
	}
	rl::RaySelector *pRaySel = dynamic_cast<rl::RaySelector*>(pSelector);
	if (pRaySel)
	{
		*ptr = pRaySel;
		return SWIGTYPE_p_rl__RaySelector;
	}
}
	
static swig_type_info *GameObject_dynamic_cast(void **ptr)
{
    rl::GameObject *pGameObject = static_cast<rl::GameObject*>(*ptr);

    rl::Creature *pCreature=dynamic_cast<rl::Creature*>(pGameObject);
    if (pCreature) {
        *ptr=pCreature;
        return SWIGTYPE_p_rl__Creature;
    }
    rl::Weapon *pWeapon=dynamic_cast<rl::Weapon*>(pGameObject);
    if (pWeapon) {
        *ptr=pWeapon;
        return SWIGTYPE_p_rl__Weapon;
    }
    rl::Armor *pArmor=dynamic_cast<rl::Armor*>(pGameObject);
    if (pArmor) {
        *ptr=pArmor;
        return SWIGTYPE_p_rl__Armor;
    }
    rl::Container *pContainer=dynamic_cast<rl::Container*>(pGameObject);
    if (pContainer) {
        *ptr=pContainer;
        return SWIGTYPE_p_rl__Container;
    }
    rl::Item *pItem=dynamic_cast<rl::Item*>(pGameObject);
    if (pItem) {
        *ptr=pItem;
        return SWIGTYPE_p_rl__Item;
    }
    return 0;
}
%}
DYNAMIC_CAST(SWIGTYPE_p_rl__GameObject, GameObject_dynamic_cast);

