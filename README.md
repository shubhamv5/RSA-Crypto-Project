A cryptographic interface based on the principle of RSA Cryptography and built in C++. It offers a multi-user message handling mechanism using file I/O in which messages, public keys and private keys are all integers. 

The interface contains 2 types of data files :

1) main database (database.txt) : used to store name of all the registered users along with their public keys.

2) user messages (name.txt) : a separate file for each user consisting of cryptic messages sent to him.

Functioning :

Option 1 : Register as a user

Register yourself as a new user to be able to receive cryptic messages. A new user is assigned a public key and a private key. The name of the user is entered into database.txt along with his public key and a separate file is created to store user messages.

Option 2 : Read messages

An already registered user can view all his messages by entering his private key. The encrypted messages are decrypted and displayed using the private key.

Option 3 : Send a message

Displayes the list of all registered users along with their public keys. A person may send a message to any of the registered user which is encrypted and stored in the user's file. 
