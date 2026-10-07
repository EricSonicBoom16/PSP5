# Authentication and credentials

## Current design
PSP5 is an offline emulator scaffold. It has no application authentication.

There is no:
- username/password database;
- OAuth or PSN login;
- JWT/session cookie;
- access or refresh token;
- API key;
- credential persistence;
- Authorization header.

## Current flow
```
local user -> PSP5 -> local loader -> emulator core
```

No authentication request is made because no remote service is contacted.

## GitHub authentication
GitHub credentials used by developers to clone/push private resources are external development credentials. They must never be compiled into PSP5 or committed to this repository.

## Future network features
If PSP5 later gains a service that requires authentication:
1. Keep secrets out of source control.
2. Perform authorization using the service's documented flow.
3. Store only the minimum token material required.
4. Prefer OS/platform secure storage where available.
5. Never log passwords, authorization codes, refresh tokens or full bearer tokens.
6. Attach access tokens only to the intended HTTPS origin.
7. Handle expiration/revocation explicitly.

Public metadata and update downloads should remain unauthenticated where practical.
