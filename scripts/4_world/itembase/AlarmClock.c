modded class AlarmClock_ColorBase
{
	// This bool flag is used for allowing the player to safely turn off the alarm clock without exploding their face
	bool m_ShouldExplode = true;

	// Reset explode flag
	override void TurnOn()
	{
		m_ShouldExplode = true;
		super.TurnOn();
	}

	// If ringing has stopped due to running out of time - drop a grenade and explode it
	override void TurnOff()
	{
		if (IsRinging() && m_ShouldExplode)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.DropGrenade, 500, false);
		}

		super.TurnOff();
	}

	// Delete grenade from alarm clock & spawn one on the ground that will explode instantly
	void DropGrenade()
	{
		ItemBase grenade = ItemBase.Cast(FindAttachmentBySlotName("VestGrenadeA"));

		if (grenade && !grenade.IsRuined())
		{
			Grenade_Base gb = Grenade_Base.Cast(grenade);
			if (gb)
			{
				gb.Delete(); // Delete grenade out of the clock

				// Get the surface coordinates at the clock's position
				vector pos = this.GetPosition();
				pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.1;

				// Create a new grande
				Grenade_Base clockGrenade = GetGame().CreateObject(grenade.GetType(), pos, false);
				clockGrenade.PlaceOnSurface(); // Place the new grenade on the ground

				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.ExplodeGrenade, 100, false, clockGrenade);
			}
		}
	}

	// Boom boom boom, I want you in my room
	void ExplodeGrenade(Grenade_Base grenade)
	{
		grenade.SetHealth(0); // Explode the grenade
	}

	// TODO: Make this work with smokes and flashbangs etc. 
	// Grenade_Base.Unpin() doesn't seem to work until it touches a player's hands which is problematic for obvious reasons. Need to investigate further
	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		Grenade_Base grenade = Grenade_Base.Cast(attachment);
		if (grenade)
		{
			string t = grenade.GetType();
			t.ToLower();
			return !t.Contains("smoke");
		}

		return false;
	}
}