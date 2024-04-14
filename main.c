#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define NUM_CATEGORIES 3
#define NUM_QUESTIONS 5
#define MAX_LENGTH 150

//Game Categories
char categories[NUM_CATEGORIES][MAX_LENGTH] = {
  "History",
  "Science",
  "Geography"
};

//Game Questions
char questions[NUM_CATEGORIES][NUM_QUESTIONS][MAX_LENGTH] = {
  {
    "Who was the first President of the United States?",
    "What was the cause of the American Civil War?",
    "When did the Great Depression occur?",
    "When did World War II start?",
    "Who was the leader of the Soviet Union during World War II?"
  },
  {
    "What is the study of matter and energy?",
    "What is the force that holds planets in orbit around the sun?",
    "What is the smallest unit of matter?",
    "What is the study of living things and their interactions with each other and their environment?",
    "What is the study of the universe and the objects in it?"
  },
  {
    "What is the capital of the United States?",
    "What is the largest ocean in the world?",
    "What is the highest mountain in the world?",
    "What is the largest desert in the world?",
    "What is the longest river in the world?"
  }
};

//Answers to the Questions
char answers[NUM_CATEGORIES][NUM_QUESTIONS][MAX_LENGTH] = {
  {
    "george_washington",
    "slavery",
    "1929",
    "1939",
    "joseph_stalin"
  },
  {
    "physics",
    "gravity",
    "atom",
    "biology",
    "astronomy"
  },
  {
    "washington_d.c.",
    "pacific_ocean",
    "mount_everest",
    "sahara_desert",
    "nile_river"
  }
};

//printing the board
int board[NUM_QUESTIONS][NUM_CATEGORIES] = {
	{100, 100, 100},
	{200, 200, 200},
	{300, 300, 300},
	{400, 400, 400},
	{500, 500, 500}
};

//function making the user answer lowercase
void answerToLower(char a[]){
	int i = 0;
	while (i < strlen(a)){
		if(a[i] == '_'){
		}
		else{
			a[i] = tolower(a[i]);
		}
		i++;
	}
};

//Wager questions
char final_question[2][150] = {
	{"Who penned this line 'It is better to be feared than loved, if you cannot be both'?"},
	{"What is the largest organ of the human body?"}
};

//Answers to the wager questions
char final_question_answer[2][20] = {
	{"machiavelli"},
	{"skin"}
};

//prints out the board
void print_board(){
	for(int c = 0; c < 3; c++){
		printf("%s ", categories[c]);	
	}
	printf("\n");
	for(int c = 0; c < 5; c++){
		for(int q = 0; q < 3; q++){
			if(board[c][q] == 0){
				printf("   %d     ", board[c][q]);
			}
			else{
				printf("   %d   ", board[c][q]);
			}
		}
		printf("\n");
	}
};

//Start of the Game
void menu(){
	printf("Welcome to Jeopardy!\n");
	printf("This is a trivia based game with two players!\n");
	printf("The rules are simple. Select a category and point value and answer the question. If the answer contains more than one word, separate the words with an underscore.\n");
	printf("Finally, at the end, once all the questions have been answered, there will be a wager!\n");
	printf("Let's begin!\n");
}

int main() {
	//declaring all variables and character arrays (strings)
	int category, question, i;
	char userAnswer[MAX_LENGTH];
	int player_1_score = 0;
	int player_2_score = 0;
	int player_1_wager = 0;
	int player_2_wager = 0;
	int points = 0; 
	char player_1_name[50];
	char player_2_name[50];
	bool player_1 = true;
	bool player_2 = false;
	
	menu();
	//Asks the two players for their names
	printf("Player 1, please enter your name: ");
	scanf("%s", &player_1_name);
	printf("Player 2, please enter your name: ");
	scanf("%s", &player_2_name);
	for(int question_completed = 0; question_completed < 15; question_completed++){
		print_board();
		//Player one 
		//Picks a question
		if(player_1 == true){
			printf("%s, Pick a category (0, 1, 2): ", player_1_name);
			scanf(" %d", &category);
			printf("%s, How much (100, 200, 300, 400, 500): ", player_1_name);
			scanf(" %d", &question);
			question = (question / 100) - 1;
			points = board[question][category];
			
			//asks for a different question if then
			// selected question has already been done
			while(points == 0){
				printf("That question has already been been picked.\nPlease pick a different category (0, 1, 2): ");
				scanf(" %d", &category);
				printf("%s, How much (100, 200, 300, 400, 500): ", player_1_name);
				scanf(" %d", &question);
				question = (question / 100) - 1;
				points = board[question][category];
			}
			//Stores user input into the variable userAnswer
			printf("\t%s\n", questions[category][question]);
			printf("%s, Enter your answer: ", player_1_name);
			scanf(" %s", userAnswer);
			answerToLower(userAnswer);
			//Checks to see if the user answer matches the correct answer
			//If the user answered correctly, their score increases by the assigned point value
			//If the user answered incorrectly, their score decreases by the assigned point value
			if (strcmp(userAnswer, answers[category][question]) == 0) {
				printf("Correct!\n");
				player_1_score = player_1_score + points;
				printf("%s's Score: %d\n", player_1_name, player_1_score);
				printf("%s's Score: %d\n", player_2_name, player_2_score);
			} else {
				printf("Incorrect. The correct answer was %s.\n", answers[category][question]);				
				player_1_score = player_1_score - points;
				printf("%s's Score: %d\n", player_1_name, player_1_score);
				printf("%s's Score: %d\n", player_2_name, player_2_score);
			}
		}
		else{
			//Player 2
			//Picks a question
			printf("%s, Pick a category (0, 1, 2): ", player_2_name);
			scanf(" %d", &category);
			printf("%s, How much (100, 200, 300, 400, 500): ", player_2_name);
			scanf(" %d", &question);
			question = (question / 100) - 1;
			
			points = board[question][category];
			
			// asks for a different question if then
			// selected question has already been done
			while(points == 0){
				printf("That question has already been been picked.\nPlease pick a different category (0, 1, 2): ");
				scanf(" %d", &category);
				printf("%s, How much (100, 200, 300, 400, 500): ", player_2_name);
				scanf(" %d", &question);
				question = (question / 100) - 1;
				points = board[question][category];
			}
			
			//Stores user input into the variable userAnswer
			printf("\t%s\n", questions[category][question]);
			printf("%s, Enter your answer: ", player_2_name);
			scanf(" %s", userAnswer);
			answerToLower(userAnswer);
			
			//Checks to see if the user answer matches the correct answer
			//If the user answered correctly, their score increases by the assigned point value
			//If the user answered incorrectly, their score decreases by the assigned point value
			if (strcmp(userAnswer, answers[category][question]) == 0) {
				printf("Correct!\n");
				player_2_score = player_2_score + points;
				printf("%s's Score: %d\n", player_2_name, player_2_score);
				printf("%s's Score: %d\n", player_1_name, player_1_score);
			} else {
				printf("Incorrect. The correct answer was %s.\n", answers[category][question]);
				player_2_score = player_2_score - points;
				printf("%s's Score: %d\n", player_2_name, player_2_score);
				printf("%s's Score: %d\n", player_1_name, player_1_score);
			}
		}
		
		//Changes the the points on the board of the question that was given
		//to 0
		board[question][category] = 0;
		player_1 = !player_1;
	}
	
	//Explains the wager/Final Question process to the user
	printf("\nAll the questions have been answered. Now, it is time for the Final Question!\n");
	printf("\nIf your score is negative, you can only wager a number equal to the absolute value of your score.\n");
	printf("Otherwise, you can choose an amount to wager, ranging from the 0 to the total you accumulated.\n");
	printf("\nIf you are correct, your points increase by the amount you wagered. If you are incorrect, you will lose that amount.\n");
	
	//the value "false" means that the user has not entered a valid wager value
	//"true" means a valid wager has been inputted
	bool wg1 = false;
	bool wg2 = false;	
	
	//Wager for Player 1
	//while a valid wager value has not been entered...
	while (wg1 == false){
		//Asks the user for their wager value
		printf("\n%s, how much would you like to wager?: ", player_1_name);
		scanf(" %d", &player_1_wager);
		//If the current score is negative, the wager input has to be the absolute value of the score.
		//The user will be asked to provide a different wager input until they enter one that meets the above specifications
		if(player_1_score < 0){
			if ((player_1_wager + player_1_score)==0 && player_1_wager > 0){
				wg1 = true;
			}
			else{
				printf("Invalid wager. Please enter a positive number equal to the absolute value of your score.\n");
				wg1 = false;
			}
		}
		//The wager input has to be positive and less than the player score
		//The user will be asked to provide a different wager input until they enter one that meets the above specifications
		else if(player_1_wager < 0 || player_1_wager > player_1_score){
			printf("Invalid wager. Please enter a number greater than 0 and less than or equal to your score.\n");
		}
		else{
			wg1 = true;
		}
	}
	
	//Wager for Player 2
	//while a valid wager value has not been entered...
	while (wg2 == false){
		//Asks the user for their wager value
		printf("\n%s, how much would you like to wager?: ", player_2_name);
		scanf(" %d", &player_2_wager);
		//If the current score is negative, the wager input has to be the absolute value of the score.
		//The user will be asked to provide a different wager input until they enter one that meets the above specifications
		if(player_2_score < 0){
			if ((player_2_wager + player_2_score)==0 && player_2_wager > 0){
				wg2 = true;
			}
			else{
				printf("Invalid wager. Please enter a positive number equal to the absolute value of your score.\n");
				wg2 = false;
			}
		}
		//The wager input has to be positive and less than the player score
		//The user will be asked to provide a different wager input until they enter one that meets the above specifications
		else if(player_2_wager < 0 || player_2_wager > player_2_score){
			printf("Invalid wager. Please enter a number greater than 0 and less than or equal to your score.\n");
		}
		else{
			wg2 = true;
		}
	}
	
	char answer1[50];
	char answer2[50];
	
	//Asks player 1 their final question
	printf("\n%s, your final question:\n %s\n", player_1_name, final_question[0]);
	scanf("%s", &answer1);
	answerToLower(answer1);
	
	//Checks to see if the user Answer is correct
	//If the answer is correct, they win the points they wagered
	if(strcmp(answer1, final_question_answer[0]) == 0){
		printf("Correct! You win %d\n", player_1_wager);
		player_1_score = player_1_score + player_1_wager;
	}
	//If the answer is incorrect, they lose the points they wagered
	else{
		printf("Incorrect! You lose %d\n", player_1_wager);
		player_1_score = player_1_score - player_1_wager;
	}
	
	//Asks player 2 their final question
	printf("\n%s, your final question:\n %s\n", player_2_name, final_question[1]);
	scanf("%s", &answer2);
	answerToLower(answer2);
	
	//Checks to see if the user Answer is correct
	//If the answer is correct, they win the points they wagered
	if(strcmp(answer2, final_question_answer[1]) == 0){
		printf("Correct! You win %d\n", player_2_wager);
		player_2_score = player_2_score + player_2_wager;
	}
	//If the answer is incorrect, they lose the points they wagered
	else{
		printf("Incorrect! You lose %d\n", player_2_wager);
		player_2_score = player_2_score - player_2_wager;
	}
	
	//final scores and ranking
	if(player_1_score > player_2_score){
		printf("\nFirst place: %s\n\tScore: %d\n", player_1_name, player_1_score);
		printf("Second place: %s\n\tScore: %d\n", player_2_name, player_2_score);
	}
	else if (player_2_score > player_1_score){
		printf("\nFirst place: %s\n\tScore: %d\n", player_2_name, player_2_score);
		printf("Second place: %s\n\tScore: %d\n", player_1_name, player_1_score);
	}
	else{
		printf("\nBoth players are tied!");
		printf("\tScore: %d", player_1_score);
	}
	return 0;
}
