class CfgPatches
{
	class ZenTimeBomb
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = { "DZ_Data" };
	};
};

class CfgMods
{
	class ZenTimeBomb
	{
		dir = "ZenTimeBomb";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "ZenTimeBomb";
		credits = "";
		author = "Zenarchist";
		authorID = "0";
		version = "1.1";
		extra = 0;
		type = "mod";
		dependencies[] =
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] =
				{
					"ZenTimeBomb/scripts/4_world"
				};
			};
		};
	};
};

class CfgVehicles
{
	// Make alarm clock with grenade attachment
	class Inventory_Base;
	class AlarmClock_ColorBase : Inventory_Base
	{
		scope = 0;
		attachments[] =
		{
			"VestGrenadeA"
		};
	}
};