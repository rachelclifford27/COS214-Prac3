#include <iostream>
#include <string>
#include <vector>

#include "Users.h"
#include "ChatRoom.h"
#include "CtrlCat.h"
#include "Dogorithm.h"
#include "Command.h"
#include "ChatIterator.h"
#include "UserIterator.h"
#include "MessageIterator.h"
#include "ChatAggregate.h"
#include "SendMessageCommand.h"
#include "LogMessageCommand.h"
#include "NotificationObserver.h"
#include "NotificationSubject.h"

/**
 * @file TestingMain.cpp
 * @brief Basic testing starting with User and ChatRoom instantiation
 * @author Rachel Clifford and Sofia Finlayson
 * @date 20/09/2025
 */

int main() {
    std::cout << "PetSpace Chat System - Basic Testing" << std::endl;
    std::cout << "Starting with User instantiation...\n" << std::endl;

    try {
        std::cout << "User Creation " << std::endl;

        User* sofia = new User("Rachel");
        User* rachel = new User("Sofia"); 
        User* bobby = new User("Bobby");

        std::cout << "Created user: " << sofia->getName() << std::endl;
        std::cout << "Created user: " << rachel->getName() << std::endl;
        std::cout << "Created user: " << bobby->getName() << std::endl;

        std::cout << "\nTesting initial user states:" << std::endl;
        std::cout << sofia->getName() << " is online: " << sofia->getOnlineStatus() << std::endl;
        std::cout << sofia->getName() << " chat rooms: " << sofia->getChatRooms().size() << std::endl;
        std::cout << sofia->getName() << " command queue: " << sofia->getCommandQueueSize() << std::endl;

        std::cout << "\nTesting online status changes:" << std::endl;
        sofia->setOnlineStatus(true);
        rachel->setOnlineStatus(true);
        bobby->setOnlineStatus(true);

        std::cout << sofia->getName() << " is now online: " << sofia->getOnlineStatus() << std::endl;
        std::cout << rachel->getName() << " is now online: " << rachel->getOnlineStatus() << std::endl;
        std::cout << bobby->getName() << " is now online: " << bobby->getOnlineStatus() << std::endl;

        std::cout << "Basic user creation test completed!\n" << std::endl;

        //mediator
        std::cout << "\nMediator Pattern" << std::endl;

        std::cout << "\nCreating chat rooms" << std::endl;

        CtrlCat* ctrlCat = new CtrlCat();
        Dogorithm* dogorithm = new Dogorithm();
        std::cout << "Chat rooms created: " << ctrlCat->getName() << " and " << dogorithm->getName() << std::endl;

        std::cout << "\nUser Registration with Chat Rooms" << std::endl;
        std::cout << "\nSofia (Name1) joining CtrlCat" << std::endl;
        sofia->joinChatRoom(ctrlCat);

        std::cout << "\nSofia (Name1) joining Dogorithm..." << std::endl;
        sofia->joinChatRoom(dogorithm);
        
        std::cout << "\nRachel (Name2) joining CtrlCat..." << std::endl;
        rachel->joinChatRoom(ctrlCat);
        
        std::cout << "\nBobby (Name3) joining Dogorithm..." << std::endl;
        bobby->joinChatRoom(dogorithm);

        std::cout << "\nVerifying Chat Room Memberships" << std::endl;
        std::cout << "CtrlCat has " << ctrlCat->getUserCount() << " users" << std::endl;
        std::cout << "Dogorithm has " << dogorithm->getUserCount() << " users" << std::endl;
        
        std::cout << "\nSofia is in " << sofia->getChatRooms().size() << " chat room(s)" << std::endl;
        std::cout << "Rachel is in " << rachel->getChatRooms().size() << " chat room(s)" << std::endl;
        std::cout << "Bobby is in " << bobby->getChatRooms().size() << " chat room(s)" << std::endl;

        std::cout << "\nTesting hasUser() method" << std::endl;
        std::cout << "CtrlCat has Sofia: " << ctrlCat->hasUser(sofia) << std::endl;
        std::cout << "CtrlCat has Rachel: " << ctrlCat->hasUser(rachel) << std::endl;
        std::cout << "CtrlCat has Bobby: " << ctrlCat->hasUser(bobby) << std::endl;
        
        std::cout << "\nDogorithm has Sofia: " << dogorithm->hasUser(sofia) << std::endl;
        std::cout << "Dogorithm has Rachel: " << dogorithm->hasUser(rachel) << std::endl;
        std::cout << "Dogorithm has Bobby: " << dogorithm->hasUser(bobby) << std::endl;
        
        std::cout << "\nTesting User Removal" << std::endl;
        std::cout << "Charlie leaving Dogorithm..." << std::endl;
        bobby->leaveChatRoom(dogorithm);
        
        std::cout << "Dogorithm now has " << dogorithm->getUserCount() << " users" << std::endl;
        std::cout << "Bobby is now in " << bobby->getChatRooms().size() << " chat room(s)" << std::endl;
        std::cout << "Dogorithm has Bobby: " << dogorithm->hasUser(bobby) << std::endl;
        
        std::cout << "\nDemonstrating Mediator" << std::endl;
        std::cout << "Sofia is in multiple rooms but users don't communicate directly" << std::endl;
        std::cout << "All communication goes through the ChatRoom mediator" << std::endl;
        std::cout << "Sofia's rooms:" << std::endl;
        for (size_t i = 0; i < sofia->getChatRooms().size(); i++) {
            std::cout << "  - " << sofia->getChatRooms()[i]->getName() << std::endl;
        }

        User* foundUser = ctrlCat->getUser("Rachel");
        std::cout << "User: " << sofia->getName() << std::endl;

        const std::vector<std::string>& history = ctrlCat->getChatHistory();
        std::cout << "Chat history: " << history.size() << std::endl;

        std::cout << "\nTesting clearChatHistory():" << std::endl;
        ctrlCat->clearChatHistory();
        std::cout << "Chat history size after clear: " << ctrlCat->getChatHistory().size() << std::endl;

        std::cout << "\nTesting getName() for both mediators:" << std::endl;
        std::cout << "Room 1 name: " << ctrlCat->getName() << std::endl;
        std::cout << "Room 2 name: " << dogorithm->getName() << std::endl;
        
        std::cout << "\nTesting clearChatHistory():" << std::endl;
        ctrlCat->clearChatHistory();

        std::cout << "Room 1 name: " << ctrlCat->getName() << std::endl;
        std::cout << "Room 2 name: " << dogorithm->getName() << std::endl;


        
        std::cout << "\nMediator pattern test completed!\n" << std::endl;

        //observer
        std::cout << "Testing Observer Pattern" << std::endl;
        
        std::cout << "\nTesting observer registration (automatic when joining rooms):" << std::endl;
        std::cout << "CtrlCat observers count: " << ctrlCat->getObservers().size() << std::endl;
        std::cout << "Dogorithm observers count: " << dogorithm->getObservers().size() << std::endl;
        
        std::cout << "\nTesting observer notifications when user joins:" << std::endl;
        std::cout << "Charlie re-joining Dogorithm..." << std::endl;
        bobby->joinChatRoom(dogorithm);
        std::cout << "Dogorithm observers count: " << dogorithm->getObservers().size() << std::endl;
        
        std::cout << "\nTesting observer notifications for status changes:" << std::endl;
        std::cout << "Rachel going offline..." << std::endl;
        rachel->setOnlineStatus(false);
        
        std::cout << "\nRachel coming back online..." << std::endl;
        rachel->setOnlineStatus(true);
        
        std::cout << "\nTesting observer notifications when user leaves:" << std::endl;
        std::cout << "Bobby leaving Dogorithm..." << std::endl;
        bobby->leaveChatRoom(dogorithm);
        std::cout << "Dogorithm observers count: " << dogorithm->getObservers().size() << std::endl;
        
        std::cout << "\nTesting offline user does not receive notifications:" << std::endl;
        rachel->setOnlineStatus(false);
        std::cout << "Bobby joining CtrlCat (Bob is offline, should not be notified)..." << std::endl;
        bobby->joinChatRoom(ctrlCat);
        
        std::cout << "\nFinal observer counts:" << std::endl;
        std::cout << "CtrlCat observers: " << ctrlCat->getObservers().size() << std::endl;
        std::cout << "Dogorithm observers: " << dogorithm->getObservers().size() << std::endl;

        std::cout << "\nTesting direct addObserver():" << std::endl;
        User* testUser = new User("TestObserver");
        testUser->setOnlineStatus(true);
        std::cout << "Dogorithm observers before: " << dogorithm->getObservers().size() << std::endl;
        dogorithm->addObserver(testUser);
        std::cout << "Dogorithm observers after addObserver: " << dogorithm->getObservers().size() << std::endl;
        
        std::cout << "\nTesting direct removeObserver():" << std::endl;
        dogorithm->removeObserver(testUser);
        std::cout << "Dogorithm observers after removeObserver: " << dogorithm->getObservers().size() << std::endl;
        
        std::cout << "\nTesting notifyObservers with different event types:" << std::endl;
        dogorithm->addObserver(sofia);
        dogorithm->notifyObservers("USER_JOINED", "TestUser");
        dogorithm->notifyObservers("USER_LEFT", "TestUser");
        dogorithm->notifyObservers("USER_ONLINE", "TestUser");
        dogorithm->notifyObservers("USER_OFFLINE", "TestUser");
        dogorithm->notifyObservers("MESSAGE_SENT", "Test message");

        std::cout << "\nTesting getObservers() return value:" << std::endl;
        const std::vector<NotificationObserver*>& observers = dogorithm->getObservers();
        std::cout << "Retrieved observers list size: " << observers.size() << std::endl;
        
        std::cout << "\nVerifying User update() receives all event types:" << std::endl;
        std::cout << "(Notifications should appear above for various event types)" << std::endl;
        
        testUser->setOnlineStatus(true);
        std::cout << "Dogorithm observers before: " << dogorithm->getObservers().size() << std::endl;
        dogorithm->addObserver(testUser);
        std::cout << "Dogorithm observers after addObserver: " << dogorithm->getObservers().size() << std::endl;
        
        dogorithm->removeObserver(testUser);
        std::cout << "Dogorithm observers after removeObserver: " << dogorithm->getObservers().size() << std::endl;
        
        std::cout << "\nTesting receiveMessage():" << std::endl;
        sofia->receiveMessage("Direct message test", rachel);

        std::cout << "\nTesting receive() with room:" << std::endl;
        sofia->receive("Test message with room", rachel, ctrlCat);
        
        User* outsider = new User("Outsider");
        outsider->setOnlineStatus(true);
        outsider->sendMessage("Fail", ctrlCat);

        std::cout << "\nTesting ChatRoom receiveMessage():" << std::endl;
        ctrlCat->receiveMessage("Test receive message", sofia);
        
        std::cout << "\nTesting getUsers():" << std::endl;
        const std::vector<User*>& usersInCtrlCat = ctrlCat->getUsers();
        std::cout << "Retrieved users list size: " << usersInCtrlCat.size() << std::endl;
        for (size_t i = 0; i < usersInCtrlCat.size(); i++) {
            std::cout << "  User " << i << ": " << usersInCtrlCat[i]->getName() << std::endl;
        }

        std::cout << "\nTesting leaving room user is not in:" << std::endl;
        User* newUser = new User("NewUser");
        newUser->setOnlineStatus(true);
        newUser->leaveChatRoom(dogorithm);
        
        std::cout << "\nObserver completed\n" << std::endl;
        
        //Command
         std::cout << "\nCOMMAND PATTERN COMPREHENSIVE TEST SUITE" << std::endl;

        // TEST 1: Basic Command Queue Operations
        std::cout << "\n--- TEST 1: Basic Command Queue Operations ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* alice = new User("Alice");
            User* bob = new User("Bob");

            alice->setOnlineStatus(true);
            bob->setOnlineStatus(true);
            alice->joinChatRoom(room);
            bob->joinChatRoom(room);

            std::cout << "Initial queue size: " << alice->getCommandQueueSize() << std::endl;
            
            alice->sendMessage("Hello World!", room);
            
            std::cout << "Queue size after execution: " << alice->getCommandQueueSize() << std::endl;

        
        }

        // TEST 2: SendMessageCommand Execution
        std::cout << "\n--- TEST 2: SendMessageCommand Execution ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* sender = new User("Sender");
            User* receiver1 = new User("Receiver1");
            User* receiver2 = new User("Receiver2");

            sender->setOnlineStatus(true);
            receiver1->setOnlineStatus(true);
            receiver2->setOnlineStatus(true);

            sender->joinChatRoom(room);
            receiver1->joinChatRoom(room);
            receiver2->joinChatRoom(room);

            sender->sendMessage("Test message from sender", room);

            std::cout << "Chat history size: " << room->getChatHistory().size() << std::endl;

        }

        // TEST 3: LogMessageCommand Execution
        std::cout << "\n--- TEST 3: LogMessageCommand Execution ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* logger = new User("Logger");

            logger->setOnlineStatus(true);
            logger->joinChatRoom(room);

            logger->sendMessage("Message to be logged", room);

        }

        // TEST 4: Multiple Commands in Sequence
        std::cout << "\n--- TEST 4: Multiple Commands in Sequence ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("MultiUser");

            user->setOnlineStatus(true);
            user->joinChatRoom(room);

            user->sendMessage("First message", room);
            user->sendMessage("Second message", room);
            user->sendMessage("Third message", room);

            std::cout << "Total messages in history: " << room->getChatHistory().size() << std::endl;

        }

        // TEST 5: Command Execution with Offline Users
        std::cout << "\n--- TEST 5: Command Execution with Offline Users ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* online = new User("OnlineUser");
            User* offline = new User("OfflineUser");

            online->setOnlineStatus(true);
            offline->setOnlineStatus(false);

            online->joinChatRoom(room);
            offline->joinChatRoom(room);

            online->sendMessage("Message from online user", room);
            offline->sendMessage("Message from offline user", room);

            std::cout << "Messages saved (should be 1): " << room->getChatHistory().size() << std::endl;

            
        }

        // TEST 6: Command Execution with Invalid Parameters
        std::cout << "\n--- TEST 6: Command Execution with Invalid Parameters ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("TestUser");

            user->setOnlineStatus(true);
            user->joinChatRoom(room);

            user->sendMessage("Test", nullptr);
            user->sendMessage("", room);

            std::cout << "Messages saved (should be 0): " << room->getChatHistory().size() << std::endl;

            
        }

        // TEST 7: User Not in ChatRoom Scenario
        std::cout << "\n--- TEST 7: User Not in ChatRoom Scenario ---" << std::endl;
        {
            ChatRoom* room1 = new ChatRoom();
            ChatRoom* room2 = new ChatRoom();
            User* user = new User("RoomSwitcher");

            user->setOnlineStatus(true);
            user->joinChatRoom(room1);

            user->sendMessage("Wrong room message", room2);

            std::cout << "Room2 messages (should be 0): " << room2->getChatHistory().size() << std::endl;

        
        }

        // TEST 8: Command Queue Management During Multiple Operations
        std::cout << "\n--- TEST 8: Command Queue Management ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("QueueTester");

            user->setOnlineStatus(true);
            user->joinChatRoom(room);

            for (int i = 0; i < 5; i++) {
                user->sendMessage("Message " + std::to_string(i), room);
            }

            std::cout << "Total messages processed: " << room->getChatHistory().size() << std::endl;
            std::cout << "Queue size after processing: " << user->getCommandQueueSize() << std::endl;

        
        }

        // TEST 9: Direct Command Creation and Execution
        std::cout << "\n--- TEST 9: Direct Command Creation and Execution ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* sender = new User("DirectSender");
            User* receiver = new User("DirectReceiver");

            sender->setOnlineStatus(true);
            receiver->setOnlineStatus(true);
            sender->joinChatRoom(room);
            receiver->joinChatRoom(room);

            Command* sendCmd = new SendMessageCommand(room, sender, "Direct send test");
            Command* logCmd = new LogMessageCommand(room, sender, "Direct log test");

            sendCmd->execute();
            logCmd->execute();

            std::cout << "Messages after direct execution: " << room->getChatHistory().size() << std::endl;

        
        }

        // TEST 10: Multiple Users, Multiple Rooms
        std::cout << "\n--- TEST 10: Multiple Users, Multiple Rooms ---" << std::endl;
        {
            ChatRoom* general = new ChatRoom();
            ChatRoom* tech = new ChatRoom();
            
            User* alice = new User("Alice");
            User* bob = new User("Bob");
            User* charlie = new User("Charlie");

            alice->setOnlineStatus(true);
            bob->setOnlineStatus(true);
            charlie->setOnlineStatus(true);

            alice->joinChatRoom(general);
            bob->joinChatRoom(general);

            bob->joinChatRoom(tech);
            charlie->joinChatRoom(tech);

            alice->sendMessage("Hello general!", general);
            bob->sendMessage("Hello tech!", tech);
            charlie->sendMessage("Tech discussion", tech);

            std::cout << "General room messages: " << general->getChatHistory().size() << std::endl;
            std::cout << "Tech room messages: " << tech->getChatHistory().size() << std::endl;

            
            
        }

        // TEST 11: Observer Notification with Commands
        std::cout << "\n--- TEST 11: Observer Notification with Commands ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* sender = new User("Sender");
            User* observer1 = new User("Observer1");
            User* observer2 = new User("Observer2");

            sender->setOnlineStatus(true);
            observer1->setOnlineStatus(true);
            observer2->setOnlineStatus(true);

            sender->joinChatRoom(room);
            observer1->joinChatRoom(room);
            observer2->joinChatRoom(room);

            sender->sendMessage("Message triggering notifications", room);

            std::cout << "Number of observers: " << room->getObservers().size() << std::endl;

            
        }

        // TEST 12: User Status Changes During Command Execution
        std::cout << "\n--- TEST 12: User Status Changes During Command Execution ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("StatusChanger");
            User* receiver = new User("Receiver");

            user->setOnlineStatus(true);
            receiver->setOnlineStatus(true);
            user->joinChatRoom(room);
            receiver->joinChatRoom(room);

            user->sendMessage("Online message", room);
            
            user->setOnlineStatus(false);
            
            user->sendMessage("Offline message", room);

            std::cout << "Messages sent (should be 1): " << room->getChatHistory().size() << std::endl;

        
        }

        // TEST 13: Memory Management and Cleanup
        std::cout << "\n--- TEST 13: Memory Management and Cleanup ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("CleanupTest");

            user->setOnlineStatus(true);
            user->joinChatRoom(room);

            user->sendMessage("Message 1", room);
            user->sendMessage("Message 2", room);
            user->sendMessage("Message 3", room);

            std::cout << "Queue size after cleanup: " << user->getCommandQueueSize() << std::endl;

            

            std::cout << "Memory cleanup completed successfully" << std::endl;
        }

        // TEST 14: Stress Test - High Volume Message Sending
        std::cout << "\n--- TEST 14: Stress Test - High Volume Messages ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* spammer = new User("Spammer");
            User* listener = new User("Listener");

            spammer->setOnlineStatus(true);
            listener->setOnlineStatus(true);
            spammer->joinChatRoom(room);
            listener->joinChatRoom(room);

            for (int i = 0; i < 100; i++) {
                spammer->sendMessage("Stress test message " + std::to_string(i), room);
            }

            std::cout << "Total messages processed: " << room->getChatHistory().size() << std::endl;

        
        }

        // TEST 15: Edge Case - Self-Messaging
        std::cout << "\n--- TEST 15: Edge Case - Self-Messaging ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("SelfTalker");

            user->setOnlineStatus(true);
            user->joinChatRoom(room);

            user->sendMessage("Talking to myself", room);

            std::cout << "Self-message saved: " << room->getChatHistory().size() << std::endl;

        
        }

        // TEST 16: Command Pattern with Room Switching
        std::cout << "\n--- TEST 16: Command Pattern with Room Switching ---" << std::endl;
        {
            ChatRoom* room1 = new ChatRoom();
            ChatRoom* room2 = new ChatRoom();
            User* user = new User("Switcher");

            user->setOnlineStatus(true);
            user->joinChatRoom(room1);
            
            user->sendMessage("Message in room1", room1);
            
            user->joinChatRoom(room2);
            user->sendMessage("Message in room2", room2);
            
            user->leaveChatRoom(room1);
            user->sendMessage("Another message in room2", room2);

            std::cout << "Room1 messages: " << room1->getChatHistory().size() << std::endl;
            std::cout << "Room2 messages: " << room2->getChatHistory().size() << std::endl;

        
        }

        // TEST 17: Null Command Handling
        std::cout << "\n--- TEST 17: Null Command Handling ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            
            room->addCommand(nullptr);
            room->executeAll();
            
            std::cout << "Null command handling completed" << std::endl;

            
        }

        // TEST 18: Message History Verification
        std::cout << "\n--- TEST 18: Message History Verification ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user1 = new User("User1");
            User* user2 = new User("User2");

            user1->setOnlineStatus(true);
            user2->setOnlineStatus(true);
            user1->joinChatRoom(room);
            user2->joinChatRoom(room);

            user1->sendMessage("First", room);
            user2->sendMessage("Second", room);
            user1->sendMessage("Third", room);

            std::cout << "Chat history:" << std::endl;
            for (const std::string& msg : room->getChatHistory()) {
                std::cout << msg;
            }

            
        }

        // TEST 19: Command Execution Order
        std::cout << "\n--- TEST 19: Command Execution Order ---" << std::endl;
        {
            ChatRoom* room = new ChatRoom();
            User* user = new User("OrderTester");

            user->setOnlineStatus(true);
            user->joinChatRoom(room);

            std::cout << "Sending messages in order: A, B, C" << std::endl;
            user->sendMessage("Message A", room);
            user->sendMessage("Message B", room);
            user->sendMessage("Message C", room);

            std::cout << "Verifying order in history:" << std::endl;
            int count = 1;
            for (const std::string& msg : room->getChatHistory()) {
                std::cout << count++ << ". " << msg;
            }

        }

        // TEST 20: Complex Scenario - Multiple Patterns Integration
        std::cout << "\n--- TEST 20: Complex Scenario - Multiple Patterns Integration ---" << std::endl;
        {
            ChatRoom* lobby = new ChatRoom();
            ChatRoom* support = new ChatRoom();
            
            User* admin = new User("Admin");
            User* user1 = new User("Customer1");
            User* user2 = new User("Customer2");
            User* support_agent = new User("SupportAgent");

            admin->setOnlineStatus(true);
            user1->setOnlineStatus(true);
            user2->setOnlineStatus(true);
            support_agent->setOnlineStatus(true);

            admin->joinChatRoom(lobby);
            user1->joinChatRoom(lobby);
            user2->joinChatRoom(lobby);
            
            support_agent->joinChatRoom(support);
            user1->joinChatRoom(support);

            admin->sendMessage("Welcome to the lobby!", lobby);
            user1->sendMessage("Hi everyone!", lobby);
            user2->sendMessage("Hello!", lobby);
            
            user1->sendMessage("I need help", support);
            support_agent->sendMessage("How can I assist you?", support);

            std::cout << "Lobby messages: " << lobby->getChatHistory().size() << std::endl;
            std::cout << "Support messages: " << support->getChatHistory().size() << std::endl;
            std::cout << "Total users in lobby: " << lobby->getUserCount() << std::endl;
            std::cout << "Total users in support: " << support->getUserCount() << std::endl;

        }


        //Iterator
         std::cout << "\nITERATOR PATTERN\n" << std::endl;

        //  Basic UserIterator Functionality
        std::cout << "\n--- Basic UserIterator Functionality ---" << std::endl;
        {
            ChatRoom* lounge = new ChatRoom();
            User* john = new User("John");
            User* sarah = new User("Sarah");
            User* mike = new User("Mike");

            john->setOnlineStatus(true);
            sarah->setOnlineStatus(true);
            mike->setOnlineStatus(true);

            john->joinChatRoom(lounge);
            sarah->joinChatRoom(lounge);
            mike->joinChatRoom(lounge);

            UserIterator* iter = lounge->createUserIterator();

            std::cout << "Iterating through users:" << std::endl;
            while (iter->hasNext()) {
                User* currentUser = iter->current();
                if (currentUser != nullptr) {
                    std::cout << "- " << currentUser->getName() << std::endl;
                }
                iter->next();
            }

        
        }

        // Basic MessageIterator Functionality
        std::cout << "\n--- Basic MessageIterator Functionality ---" << std::endl;
        {
            ChatRoom* channel = new ChatRoom();
            User* sender1 = new User("Sender1");
            User* sender2 = new User("Sender2");

            sender1->setOnlineStatus(true);
            sender2->setOnlineStatus(true);
            sender1->joinChatRoom(channel);
            sender2->joinChatRoom(channel);

            sender1->sendMessage("First message", channel);
            sender2->sendMessage("Second message", channel);
            sender1->sendMessage("Third message", channel);

            MessageIterator* msgIter = channel->createMessageIterator();

            std::cout << "Iterating through messages:" << std::endl;
            while (msgIter->hasNext()) {
                std::string msg = msgIter->currentMessage();
                std::cout << msg;
                msgIter->next();
            }

        
        }

        //  Empty Collection Iteration
        std::cout << "\n---  Empty Collection Iteration ---" << std::endl;
        {
            ChatRoom* emptyRoom = new ChatRoom();

            UserIterator* emptyUserIter = emptyRoom->createUserIterator();
            MessageIterator* emptyMsgIter = emptyRoom->createMessageIterator();

            std::cout << "Has users: " << (emptyUserIter->hasNext() ? "Yes" : "No") << std::endl;
            std::cout << "Has messages: " << (emptyMsgIter->hasNext() ? "Yes" : "No") << std::endl;

        
        }

        //  Iterator Reset and Multiple Iterations
        std::cout << "\n---  Multiple Iterator Instances ---" << std::endl;
        {
            ChatRoom* space = new ChatRoom();
            User* alex = new User("Alex");
            User* beth = new User("Beth");

            alex->setOnlineStatus(true);
            beth->setOnlineStatus(true);
            alex->joinChatRoom(space);
            beth->joinChatRoom(space);

            alex->sendMessage("Message A", space);
            beth->sendMessage("Message B", space);

            UserIterator* firstIter = space->createUserIterator();
            UserIterator* secondIter = space->createUserIterator();

            std::cout << "First iterator:" << std::endl;
            while (firstIter->hasNext()) {
                User* u = firstIter->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                firstIter->next();
            }

            std::cout << "Second iterator:" << std::endl;
            while (secondIter->hasNext()) {
                User* u = secondIter->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                secondIter->next();
            }

        
        }

        // Single Element Iteration
        std::cout << "\n--- Single Element Iteration ---" << std::endl;
        {
            ChatRoom* solo = new ChatRoom();
            User* lonely = new User("Lonely");

            lonely->setOnlineStatus(true);
            lonely->joinChatRoom(solo);
            lonely->sendMessage("All by myself", solo);

            UserIterator* singleUserIter = solo->createUserIterator();
            std::cout << "User count via iterator: ";
            int userCount = 0;
            while (singleUserIter->hasNext()) {
                userCount++;
                singleUserIter->next();
            }
            std::cout << userCount << std::endl;

            MessageIterator* singleMsgIter = solo->createMessageIterator();
            std::cout << "Message count via iterator: ";
            int msgCount = 0;
            while (singleMsgIter->hasNext()) {
                msgCount++;
                singleMsgIter->next();
            }
            std::cout << msgCount << std::endl;

            
        }

        //  Iterator Boundary Conditions
        std::cout << "\n---  Iterator Boundary Conditions ---" << std::endl;
        {
            ChatRoom* boundary = new ChatRoom();
            User* tester = new User("Tester");

            tester->setOnlineStatus(true);
            tester->joinChatRoom(boundary);

            UserIterator* boundIter = boundary->createUserIterator();

            std::cout << "Before iteration - hasNext: " << boundIter->hasNext() << std::endl;
            
            if (boundIter->hasNext()) {
                User* u = boundIter->current();
                std::cout << "Current user: " << (u ? u->getName() : "null") << std::endl;
                boundIter->next();
            }

            std::cout << "After iteration - hasNext: " << boundIter->hasNext() << std::endl;
            
            boundIter->next();
            std::cout << "After extra next() - hasNext: " << boundIter->hasNext() << std::endl;

        }

    

        //Concurrent Iterator Usage
        std::cout << "\n--- Concurrent Iterator Usage ---" << std::endl;
        {
            ChatRoom* concurrent = new ChatRoom();
            User* personA = new User("PersonA");
            User* personB = new User("PersonB");
            User* personC = new User("PersonC");

            personA->setOnlineStatus(true);
            personB->setOnlineStatus(true);
            personC->setOnlineStatus(true);

            personA->joinChatRoom(concurrent);
            personB->joinChatRoom(concurrent);
            personC->joinChatRoom(concurrent);

            UserIterator* iter1 = concurrent->createUserIterator();
            UserIterator* iter2 = concurrent->createUserIterator();

            std::cout << "Iterator 1 - First user: ";
            if (iter1->hasNext()) {
                User* u = iter1->current();
                if (u) std::cout << u->getName() << std::endl;
                iter1->next();
            }

            std::cout << "Iterator 2 - First user: ";
            if (iter2->hasNext()) {
                User* u = iter2->current();
                if (u) std::cout << u->getName() << std::endl;
                iter2->next();
            }

            std::cout << "Iterator 1 - Second user: ";
            if (iter1->hasNext()) {
                User* u = iter1->current();
                if (u) std::cout << u->getName() << std::endl;
            }

            
        }

        //Message Content Verification
        std::cout << "\n--- Message Content Verification ---" << std::endl;
        {
            ChatRoom* verification = new ChatRoom();
            User* writer = new User("Writer");
            User* reader = new User("Reader");

            writer->setOnlineStatus(true);
            reader->setOnlineStatus(true);
            writer->joinChatRoom(verification);
            reader->joinChatRoom(verification);

            writer->sendMessage("Hello", verification);
            writer->sendMessage("World", verification);
            writer->sendMessage("Test", verification);

            MessageIterator* verifyIter = verification->createMessageIterator();

            std::cout << "Verifying message content:" << std::endl;
            int position = 1;
            while (verifyIter->hasNext()) {
                std::string content = verifyIter->currentMessage();
                std::cout << "Position " << position++ << ": " << content;
                verifyIter->next();
            }

        }

        //Iterator After User Deletion
        std::cout << "\n--- Iterator Independence from Source ---" << std::endl;
        {
            ChatRoom* independent = new ChatRoom();
            User* temp1 = new User("Temp1");
            User* temp2 = new User("Temp2");

            temp1->setOnlineStatus(true);
            temp2->setOnlineStatus(true);
            temp1->joinChatRoom(independent);
            temp2->joinChatRoom(independent);

            temp1->sendMessage("Message before iterator", independent);

            UserIterator* snapshot = independent->createUserIterator();

            std::cout << "Users in iterator snapshot:" << std::endl;
            while (snapshot->hasNext()) {
                User* u = snapshot->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                snapshot->next();
            }

        
        }

        //Multiple Message Iterators
        std::cout << "\n---  Multiple Message Iterators ---" << std::endl;
        {
            ChatRoom* multiMsg = new ChatRoom();
            User* chatter = new User("Chatter");

            chatter->setOnlineStatus(true);
            chatter->joinChatRoom(multiMsg);

            chatter->sendMessage("Alpha", multiMsg);
            chatter->sendMessage("Beta", multiMsg);
            chatter->sendMessage("Gamma", multiMsg);

            MessageIterator* first = multiMsg->createMessageIterator();
            MessageIterator* second = multiMsg->createMessageIterator();

            std::cout << "First iterator messages:" << std::endl;
            while (first->hasNext()) {
                std::cout << "  " << first->currentMessage();
                first->next();
            }

            std::cout << "Second iterator messages:" << std::endl;
            while (second->hasNext()) {
                std::cout << "  " << second->currentMessage();
                second->next();
            }

        
        }

        //Iterator with User Leaving Room
        std::cout << "\n--- Iterator Before and After User Changes ---" << std::endl;
        {
            ChatRoom* changing = new ChatRoom();
            User* stayer = new User("Stayer");
            User* leaver = new User("Leaver");

            stayer->setOnlineStatus(true);
            leaver->setOnlineStatus(true);
            stayer->joinChatRoom(changing);
            leaver->joinChatRoom(changing);

            UserIterator* before = changing->createUserIterator();
            std::cout << "Users before leave:" << std::endl;
            while (before->hasNext()) {
                User* u = before->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                before->next();
            }

            leaver->leaveChatRoom(changing);

            UserIterator* after = changing->createUserIterator();
            std::cout << "Users after leave:" << std::endl;
            while (after->hasNext()) {
                User* u = after->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                after->next();
            }

        }

        // Current() Without hasNext() Check
        std::cout << "\n--- Current() Behavior at Boundaries ---" << std::endl;
        {
            ChatRoom* bounds = new ChatRoom();
            User* single = new User("Single");

            single->setOnlineStatus(true);
            single->joinChatRoom(bounds);

            UserIterator* edge = bounds->createUserIterator();

            User* beforeNext = edge->current();
            std::cout << "Current before any next(): " << (beforeNext ? beforeNext->getName() : "null") << std::endl;

            edge->next();
            User* afterNext = edge->current();
            std::cout << "Current after one next(): " << (afterNext ? afterNext->getName() : "null") << std::endl;

            edge->next();
            User* afterExtraNext = edge->current();
            std::cout << "Current after extra next(): " << (afterExtraNext ? afterExtraNext->getName() : "null") << std::endl;

        
        }

        // MessageIterator currentMessage() Edge Cases
        std::cout << "\n---  MessageIterator currentMessage() Edge Cases ---" << std::endl;
        {
            ChatRoom* msgEdge = new ChatRoom();
            User* messenger = new User("Messenger");

            messenger->setOnlineStatus(true);
            messenger->joinChatRoom(msgEdge);
            messenger->sendMessage("Only one", msgEdge);

            MessageIterator* msgCheck = msgEdge->createMessageIterator();

            std::string before = msgCheck->currentMessage();
            std::cout << "Message before next(): " << (before.empty() ? "[empty]" : before);

            msgCheck->next();
            std::string after = msgCheck->currentMessage();
            std::cout << "Message after next(): " << (after.empty() ? "[empty]" : after) << std::endl;

        
        }

        // Iterator Pattern with Multiple Rooms
        std::cout << "\n--- Iterator Pattern with Multiple Rooms ---" << std::endl;
        {
            ChatRoom* roomX = new ChatRoom();
            ChatRoom* roomY = new ChatRoom();

            User* multiRoom = new User("MultiRoom");
            User* xOnly = new User("XOnly");
            User* yOnly = new User("YOnly");

            multiRoom->setOnlineStatus(true);
            xOnly->setOnlineStatus(true);
            yOnly->setOnlineStatus(true);

            multiRoom->joinChatRoom(roomX);
            multiRoom->joinChatRoom(roomY);
            xOnly->joinChatRoom(roomX);
            yOnly->joinChatRoom(roomY);

            multiRoom->sendMessage("In X", roomX);
            multiRoom->sendMessage("In Y", roomY);

            UserIterator* xUsers = roomX->createUserIterator();
            UserIterator* yUsers = roomY->createUserIterator();

            std::cout << "Room X users:" << std::endl;
            while (xUsers->hasNext()) {
                User* u = xUsers->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                xUsers->next();
            }

            std::cout << "Room Y users:" << std::endl;
            while (yUsers->hasNext()) {
                User* u = yUsers->current();
                if (u) std::cout << "  " << u->getName() << std::endl;
                yUsers->next();
            }

        
        }

    //Nested Iteration
        std::cout << "\n--- Nested Iteration (Users and Messages) ---" << std::endl;
        {
            ChatRoom* nested = new ChatRoom();
            User* person1 = new User("Person1");
            User* person2 = new User("Person2");

            person1->setOnlineStatus(true);
            person2->setOnlineStatus(true);
            person1->joinChatRoom(nested);
            person2->joinChatRoom(nested);

            person1->sendMessage("First", nested);
            person2->sendMessage("Second", nested);

            UserIterator* userLoop = nested->createUserIterator();

            std::cout << "Nested iteration:" << std::endl;
            while (userLoop->hasNext()) {
                User* u = userLoop->current();
                if (u) {
                    std::cout << "User: " << u->getName() << std::endl;
                    
                    MessageIterator* msgLoop = nested->createMessageIterator();
                    std::cout << "  Messages in room:" << std::endl;
                    while (msgLoop->hasNext()) {
                        std::cout << "    " << msgLoop->currentMessage();
                        msgLoop->next();
                    }
                    delete msgLoop;
                }
                userLoop->next();
            }
        }

        //Complex Scenario - Full System Integration
        std::cout << "\n--- Complex Scenario - Full System Integration ---" << std::endl;
        {
            ChatRoom* mainHall = new ChatRoom();
            ChatRoom* privateRoom = new ChatRoom();

            User* admin = new User("Admin");
            User* member1 = new User("Member1");
            User* member2 = new User("Member2");
            User* guest = new User("Guest");

            admin->setOnlineStatus(true);
            member1->setOnlineStatus(true);
            member2->setOnlineStatus(true);
            guest->setOnlineStatus(true);

            admin->joinChatRoom(mainHall);
            member1->joinChatRoom(mainHall);
            member2->joinChatRoom(mainHall);
            guest->joinChatRoom(mainHall);

            admin->joinChatRoom(privateRoom);
            member1->joinChatRoom(privateRoom);

            admin->sendMessage("Welcome everyone!", mainHall);
            member1->sendMessage("Hello!", mainHall);
            member2->sendMessage("Hi there!", mainHall);

            admin->sendMessage("Private discussion", privateRoom);
            member1->sendMessage("Understood", privateRoom);

            std::cout << "\nMain Hall Users:" << std::endl;
            UserIterator* mainUsers = mainHall->createUserIterator();
            while (mainUsers->hasNext()) {
                User* u = mainUsers->current();
                if (u) std::cout << "  - " << u->getName() << std::endl;
                mainUsers->next();
            }

            std::cout << "\nPrivate Room Users:" << std::endl;
            UserIterator* privateUsers = privateRoom->createUserIterator();
            while (privateUsers->hasNext()) {
                User* u = privateUsers->current();
                if (u) std::cout << "  - " << u->getName() << std::endl;
                privateUsers->next();
            }

            std::cout << "\nMain Hall Messages:" << std::endl;
            MessageIterator* mainMsgs = mainHall->createMessageIterator();
            while (mainMsgs->hasNext()) {
                std::cout << "  " << mainMsgs->currentMessage();
                mainMsgs->next();
            }

            std::cout << "\nPrivate Room Messages:" << std::endl;
            MessageIterator* privateMsgs = privateRoom->createMessageIterator();
            while (privateMsgs->hasNext()) {
                std::cout << "  " << privateMsgs->currentMessage();
                privateMsgs->next();
            }

        }
        

    } catch (const std::exception& e) {
        std::cout << "Error during testing: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
