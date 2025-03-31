# コンパイラとフラグの設定
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address,undefined -g

# インクルードディレクトリ
MANDATORY_INCLUDES = -I./mandatory/includes
BONUS_INCLUDES = -I./bonus/includes

# 通常版のソースファイル
MANDATORY_SRCS = 	mandatory/srcs/get_next_line.c \
                	mandatory/srcs/get_next_line_utils.c \
                	mandatory/srcs/main.c 
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)
MANDATORY_NAME = get_next_line

# ボーナス版のソースファイル
BONUS_SRCS =	bonus/srcs/get_next_line_bonus.c \
            	bonus/srcs/get_next_line_utils_bonus.c \
            	bonus/srcs/main.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_NAME = get_next_line_bonus

# デフォルトターゲット
all: $(MANDATORY_NAME)

# 通常版のビルドルール
$(MANDATORY_NAME): $(MANDATORY_OBJS)
	$(CC) $(CFLAGS) $(MANDATORY_INCLUDES) -o $(MANDATORY_NAME) $(MANDATORY_OBJS)

# ボーナス版のビルドルール
bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_INCLUDES) -o $(BONUS_NAME) $(BONUS_OBJS)

# オブジェクトファイルの生成ルール
mandatory/srcs/%.o: mandatory/srcs/%.c
	$(CC) $(CFLAGS) $(MANDATORY_INCLUDES) -c $< -o $@

# ボーナス版のオブジェクトファイルの生成ルール
bonus/srcs/%.o: bonus/srcs/%.c
	$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@

# クリーンアップルール
clean:
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(MANDATORY_NAME) $(BONUS_NAME)

re: fclean all

# ボーナス版のクリーンアップ
bonus_clean: fclean
	$(RM) $(BONUS_NAME)

# ヘルプ
help:
	@echo "利用可能なターゲット:"
	@echo "  all        - 通常版をビルド"
	@echo "  bonus      - ボーナス版をビルド"
	@echo "  clean      - オブジェクトファイルを削除"
	@echo "  fclean     - すべての生成ファイルを削除"
	@echo "  re         - すべてをクリーンアップして再ビルド"
	@echo "  bonus_clean - ボーナス版の生成ファイルを削除"
	@echo "  help       - このヘルプメッセージを表示"

.PHONY: all bonus clean fclean re bonus_clean help
