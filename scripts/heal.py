"""
Example of a more complex skill with special effects
Healing skill that can restore HP
"""

def calculate_damage(attacker, defender):
    """
    Special healing move - returns negative damage to indicate healing
    
    Args:
        attacker: Dictionary with attacker's stats
        defender: Dictionary with defender's stats
        
    Returns:
        int: Negative value indicates healing amount
    """
    # Heal 30% of max HP
    heal_amount = int(attacker['max_hp'] * 0.3)
    
    print(f"[Python] {attacker['name']} uses healing move!")
    print(f"[Python] Restored {heal_amount} HP")
    
    # Return 0 damage (no damage to defender, healing is handled separately)
    return 0
