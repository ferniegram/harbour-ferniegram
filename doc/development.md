# Development notes

## Code Styling

In Fernschreiber, the code styling is very mixed. In Ferniegram, it can be mixed too. If it will not be abandoned by me, I will probably try to fix it later anyways.

## Some notes

- ~~setMessageProperties could probably be implemented better. Currently it is hardcoded in several places, including new message success callback. It is also not same as other set* chat list functions, others simply scrap data from the message, but this one sends a tdlib request. Not sure if this should also be added to handleMessageContentUpdated, handleMessageEditedUpdated or anything similar. Probably not, but who knows~~ Nevermind, messageProperties should only be received when opening a menu. That's what we do now

## Error handling

Links:
- [error tdlib object documentation](https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1error.html)
- [errors documentation in telegram API](https://core.telegram.org/api/errors) (contains a database of all errors and some more info)

406 errors are handled using [updateServiceNotification](https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1update_service_notification.html). `error` objects with them should be ignored.
This update's [TL API analog](https://core.telegram.org/constructor/updateServiceNotification) also has a boolean property `popup`. It is not yet checked if this is handled automatically by tdlib somehow.

Some other links with error databases (but, official page is better and always up-to-date):
- https://github.com/KurimuzonAkuma/pyrogram/tree/4c367aaec5b4aa9d055d1334da117487ef9fabfa/compiler/errors/source
- https://github.com/xelaj/mtproto/blob/main/errors.go