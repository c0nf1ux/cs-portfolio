package com.gamingroom.gameauth.auth;
import io.dropwizard.auth.Authorizer;
public class GameAuthorizer implements Authorizer<GameUser>
{
    @Override
    public boolean authorize(GameUser user, String role) {
        // Check if user has the role they're trying to access
        return user.getRoles() != null && user.getRoles().contains(role);
    }
}