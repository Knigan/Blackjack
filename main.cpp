#include <iostream>
#include <string>
#include <vector>
#include <ctime>

class Hand {
private:
	using ushort = unsigned short;

	class Card {
	private:
		ushort number;
		std::string name;
		ushort value;

	public:
		Card() {
			number = rand() % 13 + 1;
			switch (number) {
			case 1: 
				name = "A"; 
				value = 11; 
				break;
			case 2: 
				name = "2"; 
				value = 2; 
				break;
			case 3: 
				name = "3"; 
				value = 3; 
				break;
			case 4: 
				name = "4"; 
				value = 4; 
				break;
			case 5: 
				name = "5"; 
				value = 5; 
				break;
			case 6: 
				name = "6"; 
				value = 6; 
				break;
			case 7: 
				name = "7"; 
				value = 7; 
				break;
			case 8: 
				name = "8"; 
				value = 8; 
				break;
			case 9: 
				name = "9"; 
				value = 9; 
				break;
			case 10: 
				name = "10"; 
				value = 10; 
				break;
			case 11: 
				name = "J"; 
				value = 10; 
				break;
			case 12: 
				name = "Q"; 
				value = 10; 
				break;
			case 13: 
				name = "K"; 
				value = 10; 
				break;
			default: 
				name = ""; 
				value = 0;
			}
		}

		~Card() {}

		ushort getValue() {
			return value;
		}

		short switchValue() {
			if (value == 11) {
				value = 1;
				return 0;
			}

			if (value == 1) {
				value = 11;
				return 0;
			}

			return -1;
		}

		std::string getName() {
			return name;
		}
	};

	std::vector<Card> H;

public:
	Hand() {
		Card C1, C2;

		if (C1.getValue() + C2.getValue() > 21) {
			if (C1.getValue() == 11) {
				C1.switchValue();
			}
			else {
				C2.switchValue();
			}
		}

		H.push_back(C1);
		H.push_back(C2);
	}

	virtual ~Hand() {}

	ushort Sum() {
		ushort sum = 0;
		bool A = false;

		for (auto i = H.begin(); i != H.end(); ++i) {
			sum += i->getValue();
			if (i->getValue() == 11) {
				A = true;
			}
		}

		while (sum > 21 && A) {
			bool flag = true;
			sum = 0;

			for (auto i = H.begin(); i != H.end(); ++i) {
				if (i->getValue() == 11 && flag) {
					i->switchValue();
					flag = false;
					A = false;
				}

				sum += i->getValue();

				if (i->getValue() == 11) {
					A = true;
				}
			}
		}

		return sum;
	}

	std::string getSecondCard() {
		return H[1].getName();
	}

	std::vector<std::string> getHand() {
		std::vector<std::string> result;
		for (auto i = H.begin(); i != H.end(); ++i) {
			result.push_back(i->getName());
		}
		return result;
	}

	short addCard() {
		if (Sum() < 21) {
			Card C;
			H.push_back(C);
			return 0;
		}
		else {
			return -1;
		}
	}

	size_t getSize() {
		return H.size();
	}
};

void game(float& score, float bet) {
	bool exit = false;
	while (!exit) {

		bool flag = true;

		Hand my_hand;
		Hand dealer_hand;

		auto showMyHand = [&my_hand]() {
			auto temp = my_hand.getHand();
			std::cout << "Your hand: ";
			for (int i = 0; i < temp.size(); ++i) {
				std::cout << temp[i] + " ";
			}
			std::cout << "(sum = " << my_hand.Sum() << ")" << std::endl;
		};

		auto showDealersHand = [&dealer_hand]() {
			auto temp = dealer_hand.getHand();
			std::cout << "Dealer's hand: ";
			for (int i = 0; i < temp.size(); ++i) {
				std::cout << temp[i] + " ";
			}
			std::cout << "(sum = " << dealer_hand.Sum() << ")" << std::endl;
		};	

		if (my_hand.Sum() == 21 && dealer_hand.Sum() == 21) {
			flag = false;
		}
		else {
			if (my_hand.Sum() == 21) {
				flag = false;
			}

			if (dealer_hand.Sum() == 21) {
				flag = false;
			}
		}

		if (flag) {
			std::cout << "------------------------ The game menu ------------------------" << std::endl;
			std::cout << "1: Add a card." << std::endl;
			std::cout << "2: Check." << std::endl;
			std::cout << "3: Double the bet (only for this round)." << std::endl;
			std::cout << "4: Reduce the bet by half (only for this round)." << std::endl;
			std::cout << "5: Exit." << std::endl << std::endl;
			std::cout << "Your current score is " << score << "$." << std::endl;
			std::cout << "Your current bet is " << bet << "$." << std::endl << std::endl;
			showMyHand();
			std::cout << "Dealer's card: " << dealer_hand.getSecondCard() << std::endl;
		}

		float real_bet = bet;

		
		std::cout << std::endl;
		while (flag) {
			char symbol;
			std::cin >> symbol;

			switch (symbol) {
			case '1':
				if (my_hand.addCard() == 0) {
					std::cout << "A card was added successfully." << std::endl;
					showMyHand();
				}
				else {
					std::cout << "You already have enough cards." << std::endl;
					while (dealer_hand.Sum() < 17) {
						dealer_hand.addCard();
					}
					flag = false;
				}
				break;
			case '2':
				while (dealer_hand.Sum() < 17) {
					dealer_hand.addCard();
				}
				flag = false;
				break;
			case '3':
				if (my_hand.getSize() == 2) {
					real_bet *= 2;
					std::cout << "The bet was doubled successfully. The current bet is " << real_bet << "$. (only for this round)" << std::endl;
					my_hand.addCard();
					while (dealer_hand.Sum() < 17) {
						dealer_hand.addCard();
					}
					flag = false;
				}
				else {
					std::cout << "You cannot double your bet if you have more than 2 cards in your hand." << std::endl;
				}
				break;
			case '4':
				if (my_hand.getSize() == 2) {
					real_bet *= 0.5f;
					std::cout << "The bet was halved successfully. The current bet is " << real_bet << "$. (only for this round)" << std::endl;
				}
				else {
					std::cout << "You cannot halve your bet if you have more than 2 cards in your hand." << std::endl;
				}
				break;
			case '5':
				std::cout << "The game will be ended after this round." << std::endl;
				exit = true;
				break;
			default:
				std::cout << "You entered the wrong symbol" << std::endl;
			}

			if (my_hand.Sum() >= 21) {
				while (dealer_hand.Sum() < 17) {
					dealer_hand.addCard();
				}
				flag = false;
			}
		}

		std::cout << std::endl << "------------------------------------------------" << std::endl;
		showMyHand();
		showDealersHand();
		std::cout << std::endl;

		if (my_hand.Sum() == dealer_hand.Sum()) {
			std::cout << "Push." << std::endl;
			std::cout << "Your current score is " << score << "$." << std::endl;
			if (!exit) {
				system("pause");
				system("cls");
				continue;
			}
		}

		if (my_hand.Sum() > 21 && dealer_hand.Sum() > 21) {
			std::cout << "Draw." << std::endl;
			std::cout << "Your current score is " << score << "$." << std::endl;
			if (!exit) {
				system("pause");
				system("cls");
				continue;
			}
		}

		if (my_hand.Sum() <= 21 && (dealer_hand.Sum() < my_hand.Sum() || dealer_hand.Sum() > 21)) {
			if (my_hand.Sum() < 21) {
				std::cout << "The victory is yours! You have earned " << real_bet << "$!" << std::endl;
			}
			else {
				std::cout << "Blackjack! You have earned " << real_bet << "$!" << std::endl;
			}
			score += real_bet;
			std::cout << "Your current score is " << score << "$." << std::endl;
			if (!exit) {
				system("pause");
				system("cls");
				continue;
			}
		}
		else {
			std::cout << "You were defeated! You have lost " << real_bet << "$." << std::endl;
			score -= real_bet;
			std::cout << "Your current score is " << score << "$." << std::endl;
		}
		system("pause");
		system("cls");
	}
}

void BotVsBot(int count, float bet) {
	float score = 0.0f;
	for (int i = 0; i < count; ++i) {
		Hand my_hand;
		Hand dealer_hand;

		if (my_hand.Sum() == 21 && dealer_hand.Sum() == 21) {
			continue;
		}
		else {
			if (my_hand.Sum() == 21) {
				score += bet;
				continue;
			}

			if (dealer_hand.Sum() == 21) {
				score -= bet;
				continue;
			}
		}

		float real_bet = bet;
		if (my_hand.Sum() == 9 && (dealer_hand.getSecondCard() == "3" ||
			dealer_hand.getSecondCard() == "4" ||
			dealer_hand.getSecondCard() == "5" ||
			dealer_hand.getSecondCard() == "6")
			|| my_hand.Sum() == 10 && dealer_hand.getSecondCard() != "10" && dealer_hand.getSecondCard() != "A"
			|| my_hand.Sum() == 11 && dealer_hand.getSecondCard() != "A") 
		{
			real_bet *= 2;

			my_hand.addCard();

			while (dealer_hand.Sum() < 17) {
				dealer_hand.addCard();
			}

			if (my_hand.Sum() == dealer_hand.Sum() || my_hand.Sum() > 21 && dealer_hand.Sum() > 21) {
				continue;
			}

			if (my_hand.Sum() <= 21 && (dealer_hand.Sum() > 21 || dealer_hand.Sum() < my_hand.Sum())) {
				score += real_bet;
				continue;
			}
			else {
				score -= real_bet;
				continue;
			}
		}
		else {
			if (dealer_hand.getSecondCard() == "10" || dealer_hand.getSecondCard() == "A") {
				real_bet *= 0.5f;
			}

			while (my_hand.Sum() < 17) {
				my_hand.addCard();	
			}

			while (dealer_hand.Sum() < 17) {
				dealer_hand.addCard();
			}

			if (my_hand.Sum() == dealer_hand.Sum() || my_hand.Sum() > 21 && dealer_hand.Sum() > 21) {
				continue;
			}

			if (my_hand.Sum() <= 21 && (dealer_hand.Sum() > 21 || dealer_hand.Sum() < my_hand.Sum())) {
				score += real_bet;
				continue;
			}
			else {
				score -= real_bet;
				continue;
			}
		}
	}

	std::cout << "The current score is " << score << "$ with the bet in " << bet << "$." << std::endl;
}

int main() {
	srand(time(nullptr));

	float score = 0.0f;
	float bet = 1.0f;
	bool exit = false;

	while (!exit) {
		char symbol;
		std::cout << "------------------------ The main menu ------------------------" << std::endl;
		std::cout << "1: Play." << std::endl;
		std::cout << "2: Change your bet (default is 1$)." << std::endl;
		std::cout << "3: Exit." << std::endl;
		std::cout << "4: A battle of bots" << std::endl << std::endl;
		std::cout << "Your current score is " << score << "$." << std::endl;
		std::cout << "Your current bet is " << bet << "$." << std::endl;
		std::cin >> symbol;

		switch (symbol) {
		case '1':
			std::cout << "The game is started!" << std::endl << std::endl;
			game(score, bet);
			std::cout << "------------------------ The main menu ------------------------" << std::endl;
			std::cout << "1: Play." << std::endl;
			std::cout << "2: Change your bet (default is 1$)." << std::endl;
			std::cout << "3: Exit." << std::endl << std::endl;
			std::cout << "Your current score is " << score << "$." << std::endl;
			std::cout << "Your current bet is " << bet << "$." << std::endl;
			break;
		case '2':
			std::cout << "Enter a desired bet." << std::endl;
			std::cin >> bet;
			std::cout << "Your current bet is " << bet << "$." << std::endl << std::endl;
			break;
		case '3':
			exit = true;
			break;
		case '4': 
			int count;
			std::cout << "Enter a count of games, that will be played by bots" << std::endl;
			std::cin >> count;
			BotVsBot(count, bet);
			break;
		default:
			std::cout << "You entered the wrong symbol" << std::endl;
		}
	}

	return 0;
}
